"""Bounded differential checks of three recovered predicates, not the full module."""
import ctypes
import hashlib
import json
import random
import struct
from collections import Counter

from bounded_arm64 import Arm64Fixture, DATA, ROOT
from unicorn.arm64_const import UC_ARM64_REG_W8, UC_ARM64_REG_X25


def main():
    library_path = ROOT / 'build/host/prism_observed_models.dll'
    library = ctypes.CDLL(str(library_path))
    library.prism_tracer_positive.argtypes = [ctypes.c_int32]
    library.prism_filter_exceeds.argtypes = [ctypes.c_int32, ctypes.c_uint32]
    library.prism_reason_accepted.argtypes = [ctypes.c_uint8]
    for name in ['prism_tracer_positive', 'prism_filter_exceeds',
                 'prism_reason_accepted']:
        getattr(library, name).restype = ctypes.c_bool
    fixture = Arm64Fixture()
    rng = random.Random(0x50524544)
    cases = []

    def stop(address):
        def handler(current):
            current.reason = f'slice_stop:{address:#x}'
            current.uc.emu_stop()
        return handler

    def record(kind, inputs, trace, expected, actual, complete):
        cases.append({'kind': kind, 'inputs': inputs, 'trace': trace,
                      'original': expected, 'model': actual,
                      'passed': complete and expected == actual})
        if len(cases) % 32 == 0:
            print(f'Completed {len(cases)} bounded cases', flush=True)

    boundaries = [-2147483648, -2147483647, -65536, -2, -1, 0, 1, 2,
                  9, 10, 255, 65536, 2147483646, 2147483647]
    for value in boundaries + [rng.randint(-2147483648, 2147483647)
                               for _ in range(64)]:
        fixture.reset()
        fixture.handlers = {address: stop(address)
                            for address in [0x410700, 0x410734]}
        fixture.uc.reg_write(UC_ARM64_REG_W8, value & 0xffffffff)
        trace = fixture.run(0x4106f8, [], count=32, timeout_us=100000)
        complete = trace['reason'].startswith('slice_stop:')
        record('tracer_slice', {'value': value}, trace,
               trace['pc'] == '0x410700',
               bool(library.prism_tracer_positive(value)), complete)

    layers = [0, 1, 2, 9, 0x7ffffffe, 0x7fffffff, 0x80000000,
              0xfffffffe, 0xffffffff]
    vectors = [(observed, layer) for observed in boundaries for layer in layers]
    vectors += [(rng.randint(-2147483648, 2147483647), rng.getrandbits(32))
                for _ in range(64)]
    for observed, layer in vectors:
        fixture.reset()
        fixture.handlers = {address: stop(address)
                            for address in [0x47e0d0, 0x47e0f4]}
        fixture.uc.mem_write(DATA, struct.pack('<I', layer))
        fixture.uc.reg_write(UC_ARM64_REG_X25, DATA)
        fixture.uc.reg_write(UC_ARM64_REG_W8, observed & 0xffffffff)
        trace = fixture.run(0x47e0a4, [], count=32, timeout_us=100000)
        complete = trace['reason'].startswith('slice_stop:')
        record('filter_slice', {'observed': observed, 'layer_bits': hex(layer)},
               trace, trace['pc'] == '0x47e0d0',
               bool(library.prism_filter_exceeds(observed, layer)), complete)

    for reason in range(256):
        fixture.reset()
        fixture.handlers = {}
        trace = fixture.run(0x47f2c8, [reason], count=20000, timeout_us=100000)
        record('reason_function', {'reason': reason}, trace,
               bool(trace['return']), bool(library.prism_reason_accepted(reason)),
               trace['reason'] == 'returned')

    failures = [case for case in cases if not case['passed']]
    result = {
        'scope': 'two original instruction slices plus original reason function',
        'excluded': ['TracerPid acquisition', 'seccomp acquisition',
                     'handler provenance classifier', 'full-module behavior',
                     'JNI integration', 'Android device execution'],
        'sample_sha256': hashlib.sha256((ROOT.parent / 'libprism-sun.so').read_bytes()).hexdigest(),
        'library_sha256': hashlib.sha256(library_path.read_bytes()).hexdigest(),
        'seed': '0x50524544', 'total': len(cases),
        'counts': dict(Counter(case['kind'] for case in cases)),
        'passed': len(cases) - len(failures), 'failures': failures, 'cases': cases,
    }
    (ROOT / 'evidence/differential_models.json').write_text(json.dumps(result, indent=2))
    print(json.dumps({key: result[key] for key in ['total', 'passed', 'counts', 'failures']}), flush=True)
    return int(bool(failures))


if __name__ == '__main__':
    raise SystemExit(main())
