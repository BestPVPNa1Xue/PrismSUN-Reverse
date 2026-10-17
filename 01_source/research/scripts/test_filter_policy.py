"""Original flag-update flow with explicit acquisition and string-operation mocks."""
import ctypes
import hashlib
import itertools
import json
import random
import struct

from bounded_arm64 import Arm64Fixture, DATA, OUTPUT, ROOT
from unicorn.arm64_const import UC_ARM64_REG_X0, UC_ARM64_REG_X1, UC_ARM64_REG_X8


class Flags(ctypes.Structure):
    _fields_ = [('acceptable', ctypes.c_uint8), ('excessive_count', ctypes.c_uint8),
                ('suspicious_handler', ctypes.c_uint8), ('status_failed', ctypes.c_uint8),
                ('observed', ctypes.c_int32), ('reason', ctypes.c_uint8)]


def main():
    path = ROOT / 'build/host/prism_observed_models.dll'
    library = ctypes.CDLL(str(path))
    library.prism_filter_policy.argtypes = [ctypes.c_bool, ctypes.c_int32,
                                          ctypes.c_uint32, ctypes.c_bool,
                                          ctypes.c_uint8, ctypes.POINTER(Flags)]
    library.prism_filter_policy.restype = None
    fixture = Arm64Fixture()
    cases = []
    vectors = list(itertools.product([False, True], [-2147483648, -1, 0, 1, 2, 3, 2147483647],
                                    [0, 1, 0x7fffffff, 0xffffffff], [False, True],
                                    [0, 9, 10, 11, 12, 255]))
    rng = random.Random(0x53494753)
    vectors += [(bool(rng.getrandbits(1)), rng.randint(-2147483648, 2147483647),
                 rng.getrandbits(32), bool(rng.getrandbits(1)), rng.randrange(256))
                for _ in range(32)]
    for status_failed, observed, layer, handler_failed, reason in vectors:
        fixture.reset()
        fixture.uc.mem_write(DATA + 4, struct.pack('<i', observed))
        fixture.uc.mem_write(OUTPUT, b'\xa5' * 80)
        fixture.uc.reg_write(UC_ARM64_REG_X8, OUTPUT)
        copies = []
        classifier_inputs = []

        def init_string(current):
            address = current.uc.reg_read(UC_ARM64_REG_X0)
            current.uc.mem_write(address, bytes(24))
            current.return_value(address)

        def status_result(current):
            current.uc.reg_write(UC_ARM64_REG_X1, 0)
            current.return_value(DATA)

        def classified(current):
            classifier_inputs.append([current.uc.reg_read(register)
                                      for register in [UC_ARM64_REG_X0, UC_ARM64_REG_X1]])
            current.return_value(reason)

        def copy_string(current):
            copies.append([current.uc.reg_read(register)
                           for register in [UC_ARM64_REG_X0, UC_ARM64_REG_X1]])
            current.return_value(0)

        fixture.handlers = {
            0xf7768: init_string,
            0x4c02b4: status_result,
            0x47e398: lambda current: current.return_value(int(status_failed)),
            0x47e7f4: lambda current: current.return_value(DATA),
            0x46dc28: lambda current: current.return_value(0),
            0x47eb78: lambda current: current.return_value(int(handler_failed)),
            0x47ef98: lambda current: current.return_value(DATA + 0x1000),
            0x471c8c: classified,
            0x745e64: copy_string,
            0x4c02b8: lambda current: current.return_value(0),
        }
        trace = fixture.run(0x47df58, [layer], count=4000, timeout_us=100000)
        raw = bytes(fixture.uc.mem_read(OUTPUT, 80))
        original = dict(zip(['acceptable', 'excessive_count', 'suspicious_handler', 'status_failed'], raw[:4]))
        original['observed'] = struct.unpack_from('<i', raw, 4)[0]
        original['reason'] = raw[32]
        model = Flags()
        library.prism_filter_policy(status_failed, observed, layer, handler_failed,
                                    reason, ctypes.byref(model))
        actual = {name: getattr(model, name) for name, _ in Flags._fields_}
        expected_copies = int(bool(model.suspicious_handler))
        guard_ok = raw[64:] == b'\xa5' * 16
        passed = (trace['reason'] == 'returned' and original == actual and guard_ok
                  and len(copies) == expected_copies
                  and len(classifier_inputs) == int(not handler_failed))
        cases.append({'inputs': {'status_failed': status_failed, 'observed': observed,
                                 'layer': hex(layer), 'handler_failed': handler_failed,
                                 'reason': reason}, 'passed': passed, 'trace': trace,
                      'original': original, 'model': actual, 'guard_ok': guard_ok,
                      'string_copy_calls': copies, 'classifier_inputs': classifier_inputs})
        if len(cases) % 64 == 0:
            print(f'Completed {len(cases)} policy cases with mocked acquisition', flush=True)
    failures = [case for case in cases if not case['passed']]
    result = {'scope': 'original 0x47df58 flag-update control flow; explicit dependency mocks',
              'mocked_addresses': [hex(address) for address in fixture.handlers],
              'excluded': ['status parsing', 'SIGSYS acquisition', 'reason production',
                           'C++ string ABI and contents', 'exception paths',
                           'real-device execution', 'full-module equivalence'],
              'sample_sha256': hashlib.sha256((ROOT.parent / 'libprism-sun.so').read_bytes()).hexdigest(),
              'library_sha256': hashlib.sha256(path.read_bytes()).hexdigest(),
              'seed': '0x53494753', 'total': len(cases),
              'passed': len(cases) - len(failures), 'failures': failures, 'cases': cases}
    (ROOT / 'evidence/differential_policy.json').write_text(json.dumps(result, indent=2))
    print(json.dumps({key: result[key] for key in ['total', 'passed', 'failures']}), flush=True)
    return int(bool(failures))


if __name__ == '__main__':
    raise SystemExit(main())
