"""Compare event-22 selection with original instructions and JNI-table fixtures."""
import ctypes
import hashlib
import itertools
import json
import random
import struct

from bounded_arm64 import Arm64Fixture, DATA, OUTPUT, ROOT, SENTINEL
from unicorn.arm64_const import UC_ARM64_REG_X0, UC_ARM64_REG_X1, UC_ARM64_REG_X8

ENV = DATA + 0x1000
TABLE = DATA + 0x2000
LIST = DATA + 0x4000
NODES = DATA + 0x5000
NAMES = DATA + 0x6000
CLASSES = DATA + 0x8000
FIND = SENTINEL + 0x100
CHECK = SENTINEL + 0x104
CLEAR = SENTINEL + 0x108
DELETE = SENTINEL + 0x10c


class Outcome(ctypes.Structure):
    _fields_ = [('found', ctypes.c_uint8), ('exception', ctypes.c_uint8)]


class Result(ctypes.Structure):
    _fields_ = [(name, ctypes.c_uint32) for name in
                ['queried', 'selected', 'cleared', 'deleted', 'event', 'acquisition_failed']]


def main():
    path = ROOT / 'build/host/prism_class_probe.dll'
    library = ctypes.CDLL(str(path))
    library.prism_model_class_probe.argtypes = [ctypes.c_uint8, ctypes.c_uint8,
                                              ctypes.POINTER(Outcome), ctypes.c_uint32,
                                              ctypes.POINTER(ctypes.c_uint32), ctypes.POINTER(Result)]
    library.prism_model_class_probe.restype = None
    fixture = Arm64Fixture()
    patterns = [list(pattern) for count in range(4)
                for pattern in itertools.product([(0, 0), (1, 0), (0, 1), (1, 1)], repeat=count)]
    vectors = [(configured, ready, pattern) for configured, ready, pattern in
               itertools.product([0, 1], [0, 1], patterns)]
    rng = random.Random(0x434c4153)
    vectors += [(rng.choice([0, 1, 2, 3, 128, 255]), rng.choice([0, 1, 2, 3, 128, 255]),
                 [(rng.choice([0, 1, 128, 255]), rng.choice([0, 1, 128, 255]))
                  for _ in range(rng.randrange(17))]) for _ in range(64)]
    cases = []
    for case_index, (configured, ready, pattern) in enumerate(vectors):
        count = len(pattern)
        fixture.reset()
        fixture.uc.mem_write(ENV, struct.pack('<Q', TABLE))
        for offset, target in [(48, FIND), (1824, CHECK), (136, CLEAR), (184, DELETE)]:
            fixture.uc.mem_write(TABLE + offset, struct.pack('<Q', target))
        fixture.uc.mem_write(LIST + 16, struct.pack('<Q', NODES if count else 0))
        for index in range(count):
            fixture.uc.mem_write(NODES + index * 32,
                                 struct.pack('<Q', NODES + (index + 1) * 32 if index + 1 < count else 0))
        fixture.uc.mem_write(OUTPUT, b'\xa5' * 64)
        state = {'queried': [], 'cleared': [], 'deleted': [], 'selected': [],
                 'events': [], 'diagnostics': [], 'jni_arguments_ok': True, 'current': None}

        def args(current):
            return [current.uc.reg_read(register) for register in [UC_ARM64_REG_X0, UC_ARM64_REG_X1]]

        def find_class(current):
            environment, name = args(current)
            index = (name - NAMES) // 32
            valid = environment == ENV and name == NAMES + index * 32 and 0 <= index < count
            state['jni_arguments_ok'] &= valid
            if not valid:
                raise AssertionError('Unexpected FindClass arguments')
            state['current'] = index
            state['queried'].append(index)
            current.return_value(CLASSES + index * 32 if pattern[index][0] else 0)

        def exception_check(current):
            state['jni_arguments_ok'] &= args(current)[0] == ENV
            current.return_value(pattern[state['current']][1])

        def exception_clear(current):
            state['jni_arguments_ok'] &= args(current)[0] == ENV
            state['cleared'].append(state['current'])
            current.return_value(0)

        def delete_ref(current):
            environment, reference = args(current)
            index = state['current']
            state['jni_arguments_ok'] &= environment == ENV and reference == CLASSES + index * 32
            state['deleted'].append(index)
            current.return_value(0)

        def append(current):
            state['selected'].append((args(current)[1] - NAMES) // 32)
            current.return_value(0)

        def event(current):
            state['events'].append(args(current)[0])
            current.return_value(0)

        def diagnostic(current):
            state['diagnostics'].append(args(current)[0])
            current.return_value(args(current)[0])

        def acquire(current):
            address = current.uc.reg_read(UC_ARM64_REG_X8)
            current.uc.mem_write(address, struct.pack('<QQB', 0, ENV, 0))
            current.return_value(address)

        fixture.handlers = {
            0x6b6954: lambda current: current.return_value(0),
            0x6b6958: lambda current: current.return_value(0),
            0x6b695c: lambda current: current.return_value(configured),
            0x306df0: acquire,
            0x6ae7d0: lambda current: current.return_value(ready),
            0x6b0660: lambda current: current.return_value(ENV),
            0x6b0998: lambda current: current.return_value(LIST),
            0x2a665c: lambda current: current.return_value(1),
            0x2a6598: lambda current: current.return_value(NAMES + ((args(current)[0] - NODES) // 32) * 32),
            0x4dae04: lambda current: current.return_value(DATA + 0x9000),
            0x2a829c: lambda current: current.return_value(args(current)[0]),
            0x6b6964: append,
            0x6b6968: lambda current: current.return_value(0),
            0x6b696c: lambda current: current.return_value(DATA + 0x9000),
            0x634e84: event,
            0x2d94e4: lambda current: current.return_value(0),
            0x6aec38: lambda current: current.return_value(DATA + 0xa000),
            0x6afc4c: lambda current: current.return_value(DATA + 0xa000),
            0x2b2208: diagnostic,
            0xc7be8: lambda current: current.return_value(0),
            0x6b00fc: lambda current: current.return_value(0),
            0x74539c: lambda current: current.return_value(0),
            FIND: find_class, CHECK: exception_check, CLEAR: exception_clear, DELETE: delete_ref,
        }
        fixture.uc.reg_write(UC_ARM64_REG_X8, OUTPUT)
        trace = fixture.run(0x6ab3d8, [DATA, DATA + 0x100], count=30000, timeout_us=200000)
        original_wrappers = [hex(address) for address in [0x2dce08, 0x3079bc, 0x307d30, 0x301194]
                             if address in fixture.visited]
        outcomes = (Outcome * max(count, 1))(*[Outcome(*values) for values in pattern])
        indices = (ctypes.c_uint32 * (count + 4))(*([0xffffffff] * (count + 4)))
        result_buffer = (ctypes.c_uint8 * (ctypes.sizeof(Result) + 16))()
        ctypes.memset(result_buffer, 0xa5, ctypes.sizeof(result_buffer))
        result = Result.from_buffer(result_buffer)
        library.prism_model_class_probe(configured, ready, outcomes, count, indices, ctypes.byref(result))
        expected_queries = list(range(result.queried))
        expected_clears = [index for index in expected_queries if pattern[index][1]]
        expected_selected = list(indices[:result.selected])
        output_guard = bytes(result_buffer)[ctypes.sizeof(Result):] == b'\xa5' * 16
        index_guard = all(value == 0xffffffff for value in indices[result.selected:])
        original_guard = bytes(fixture.uc.mem_read(OUTPUT, 64)) == b'\xa5' * 64
        passed = (trace['reason'] == 'returned' and state['queried'] == expected_queries
                  and state['selected'] == expected_selected and state['deleted'] == expected_selected
                  and len(state['deleted']) == result.deleted and state['cleared'] == expected_clears
                  and len(state['cleared']) == result.cleared
                  and state['events'] == ([result.event] if result.event else [])
                  and state['diagnostics'] == ([0xbba] if result.acquisition_failed else [])
                  and state['jni_arguments_ok'] and output_guard and index_guard and original_guard)
        cases.append({'inputs': {'configured': configured, 'environment_ready': ready, 'outcomes': pattern},
                      'passed': passed, 'state': state, 'model': {name: getattr(result, name) for name, _ in Result._fields_},
                      'model_selected_indices': expected_selected, 'original_wrappers': original_wrappers,
                      'output_guard': output_guard, 'index_guard': index_guard, 'original_guard': original_guard,
                      'trace': trace})
        if (case_index + 1) % 32 == 0:
            print(f'Completed {case_index + 1} class-probe cases', flush=True)
    failures = [case for case in cases if not case['passed']]
    result = {'scope': 'Original event-22 control flow and four original JNI wrappers versus compiled outcome model',
              'mocked_addresses': [hex(address) for address in fixture.handlers],
              'executed_original_wrappers': ['0x2dce08', '0x3079bc', '0x307d30', '0x301194'],
              'excluded': ['JNI acquisition', 'configuration parsing and provenance', 'real class-loader behavior',
                           'container and string internals', 'JNI detach and object lifetimes', 'result object ABI',
                           'network transmission', 'real-device execution', 'full-module equivalence'],
              'sample_sha256': hashlib.sha256((ROOT.parent / 'libprism-sun.so').read_bytes()).hexdigest(),
              'library_sha256': hashlib.sha256(path.read_bytes()).hexdigest(),
              'seed': '0x434c4153', 'total': len(cases), 'passed': len(cases) - len(failures),
              'failures': failures, 'cases': cases}
    (ROOT / 'evidence/differential_class_probe.json').write_text(json.dumps(result, indent=2))
    print(json.dumps({'total': len(cases), 'passed': result['passed'], 'failure_count': len(failures)}), flush=True)
    return int(bool(failures))


if __name__ == '__main__':
    raise SystemExit(main())
