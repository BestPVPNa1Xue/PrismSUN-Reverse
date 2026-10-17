"""Compare original ring-reader control flow with a compiled snapshot model."""
import ctypes
import hashlib
import itertools
import json
import random
import struct

from bounded_arm64 import Arm64Fixture, OUTPUT, ROOT
from unicorn.arm64_const import UC_ARM64_REG_X0, UC_ARM64_REG_X1, UC_ARM64_REG_X2, UC_ARM64_REG_X8

RING = 0x20000000
MASK = 0xffffffff


class Plan(ctypes.Structure):
    _fields_ = [('status', ctypes.c_uint32), ('next_read', ctypes.c_uint32),
                ('declared_size', ctypes.c_uint32), ('copied_size', ctypes.c_uint32),
                ('type', ctypes.c_uint8), ('slot_count', ctypes.c_uint8),
                ('resize_required', ctypes.c_uint8), ('reserved', ctypes.c_uint8),
                ('chunks', ctypes.c_uint16 * 16)]


def main():
    path = ROOT / 'build/host/prism_shared_ring.dll'
    library = ctypes.CDLL(str(path))
    library.prism_plan_ring_read.argtypes = [ctypes.c_uint32, ctypes.c_uint32,
                                           ctypes.POINTER(ctypes.c_uint8), ctypes.POINTER(Plan)]
    library.prism_plan_ring_read.restype = None
    fixture = Arm64Fixture()
    rng = random.Random(0x52494e47)
    vectors = [(reader, available, slots, total, kind)
               for reader, available, slots, total, kind in itertools.product(
                   [0, 15, 255, 0xfffffff8, MASK], [0, 1, 15, 16, MASK],
                   [0, 1, 2, 16, 17, 255], [0, 1, 0xff80, 0xff81], [19])]
    vectors += [(rng.getrandbits(32), rng.choice([0, 1, 2, 8, 15, 16, 17, MASK]),
                 rng.choice([0, 1, 2, 8, 16, 17, 255]),
                 rng.choice([0, 1, 4088, 8176, 0xff80, 0xff81, MASK]), rng.randrange(256))
                for _ in range(48)]
    cases = []
    for case_index, (reader, available, slot_count, total, kind) in enumerate(vectors):
        writer = (reader + available) & MASK
        slots = bytearray(16 * 4096)
        lengths = [rng.choice([0, 1, 7, 4087, 4088, 4089, 65535]) for _ in range(16)]
        for index in range(16):
            struct.pack_into('<H', slots, index * 4096 + 6, lengths[index])
        first = (reader & 15) * 4096
        struct.pack_into('<IBB', slots, first, total, kind, slot_count)
        fixture.reset()
        fixture.uc.mem_write(RING, struct.pack('<II', writer, reader) + bytes(slots) + b'\xa5' * 16)
        fixture.uc.mem_write(OUTPUT, b'\xa5' * 64)
        fixture.uc.reg_write(UC_ARM64_REG_X8, OUTPUT)
        state = {'chunks': [], 'loads': [], 'stores': [], 'resize': [], 'record_type': None}
        strings = {}

        def arguments(current):
            return [current.uc.reg_read(register) for register in
                    [UC_ARM64_REG_X0, UC_ARM64_REG_X1, UC_ARM64_REG_X2]]

        def load(current):
            address, order, _ = arguments(current)
            state['loads'].append([address - RING, order])
            current.return_value(struct.unpack('<I', current.uc.mem_read(address, 4))[0])

        def store(current):
            address, value, order = arguments(current)
            state['stores'].append([address - RING, value & MASK, order])
            current.uc.mem_write(address, struct.pack('<I', value & MASK))
            current.return_value(address)

        def initialize(current):
            address, _, _ = arguments(current)
            strings[address] = 0
            current.return_value(address)

        def append(current):
            address, source, size = arguments(current)
            state['chunks'].append([source - RING, size])
            strings[address] += size
            current.return_value(address)

        def length(current):
            address, _, _ = arguments(current)
            current.return_value(strings[address])

        def resize(current):
            address, size, _ = arguments(current)
            state['resize'].append(size)
            strings[address] = size
            current.return_value(address)

        def ready(current):
            _, record, _ = arguments(current)
            state['record_type'] = current.uc.mem_read(record, 1)[0]
            current.return_value(0)

        fixture.handlers = {
            0x591164: load, 0x591620: store, 0xf7768: initialize,
            0x59383c: lambda current: current.return_value(0),
            0x7457ac: append, 0xd038c: length, 0x2a067c: resize,
            0x593840: lambda current: current.return_value(0),
            0x51f85c: ready, 0x51fc30: lambda current: current.return_value(0),
            0x4e0f04: lambda current: current.return_value(0),
            0x74539c: lambda current: current.return_value(0),
        }
        trace = fixture.run(0x591e24, [RING], count=4000, timeout_us=100000)
        branches = [(0, 0x591f70), (1, 0x59200c), (2, 0x592058),
                    (3, 0x5920c4), (4, 0x5920e0)]
        visited_status = [status for status, address in branches if address in fixture.visited]
        original_next = struct.unpack('<I', fixture.uc.mem_read(RING + 4, 4))[0]
        array = (ctypes.c_uint8 * len(slots)).from_buffer(slots)
        plan = Plan()
        library.prism_plan_ring_read(writer, reader, array, ctypes.byref(plan))
        expected_chunks = []
        if plan.status == 4:
            expected_chunks = [[8 + ((reader + index) & 15) * 4096 + 8, plan.chunks[index]]
                               for index in range(plan.slot_count)]
        expected_stores = [[4, plan.next_read, 3]] if plan.status in [1, 2, 4] else []
        guard_ok = bytes(fixture.uc.mem_read(RING + 65544, 16)) == b'\xa5' * 16
        output_guard_ok = bytes(fixture.uc.mem_read(OUTPUT, 64)) == b'\xa5' * 64
        snapshot_ok = bytes(fixture.uc.mem_read(RING + 8, 65536)) == bytes(slots)
        expected_type = plan.type if plan.status == 4 else None
        expected_resize = [plan.declared_size] if plan.resize_required else []
        passed = (trace['reason'] == 'returned' and visited_status == [plan.status]
                  and original_next == plan.next_read and state['chunks'] == expected_chunks
                  and state['stores'] == expected_stores and state['resize'] == expected_resize
                  and state['loads'] == [[4, 0], [0, 2]]
                  and state['record_type'] == expected_type and guard_ok
                  and output_guard_ok and snapshot_ok)
        cases.append({'inputs': {'reader': reader, 'writer': writer, 'slot_count': slot_count,
                                 'declared_size': total, 'type': kind, 'lengths': lengths},
                      'passed': passed, 'original_status': visited_status,
                      'original_next': original_next, 'model_status': plan.status,
                      'model_next': plan.next_read, 'state': state,
                      'guard_ok': guard_ok, 'output_guard_ok': output_guard_ok,
                      'snapshot_ok': snapshot_ok, 'trace': trace})
        if (case_index + 1) % 64 == 0:
            print(f'Completed {case_index + 1} ring-reader cases', flush=True)
    failures = [case for case in cases if not case['passed']]
    result = {'scope': 'original 0x591e24 control flow versus compiled stable-snapshot plan',
              'mocked_addresses': [hex(address) for address in fixture.handlers],
              'excluded': ['counter atomic wrapper internals', 'concurrent publication',
                           'C++ optional/string ABI', 'payload byte copying', 'allocation failures',
                           'exception paths', 'real-device execution', 'full-module equivalence'],
              'sample_sha256': hashlib.sha256((ROOT.parent / 'libprism-sun.so').read_bytes()).hexdigest(),
              'library_sha256': hashlib.sha256(path.read_bytes()).hexdigest(),
              'seed': '0x52494e47', 'total': len(cases), 'passed': len(cases) - len(failures),
              'failures': failures, 'cases': cases}
    (ROOT / 'evidence/differential_shared_ring.json').write_text(json.dumps(result, indent=2))
    print(json.dumps({'total': len(cases), 'passed': result['passed'], 'failure_count': len(failures)}), flush=True)
    return int(bool(failures))


if __name__ == '__main__':
    raise SystemExit(main())
