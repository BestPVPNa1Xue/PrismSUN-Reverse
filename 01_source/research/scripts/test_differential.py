"""Compare compiled helper bodies against unmodified original instructions."""
import ctypes
import hashlib
import json
import random

from bounded_arm64 import Arm64Fixture, DATA, OUTPUT, ROOT


def main():
    library_path = ROOT / 'build/host/prism_helpers.dll'
    library = ctypes.CDLL(str(library_path))
    library.prism_xor_cycle64.argtypes = [ctypes.c_void_p, ctypes.c_size_t,
                                        ctypes.c_uint64]
    library.prism_xor_cycle64.restype = None
    library.prism_hex_encode.argtypes = [ctypes.c_void_p, ctypes.c_void_p,
                                        ctypes.c_size_t, ctypes.c_bool]
    library.prism_hex_encode.restype = None
    rng = random.Random(0x505249534d)
    fixture = Arm64Fixture()
    cases = []
    failures = []
    vectors = [(bytes.fromhex('75922f9dd65912a1'), 0xa12f2bb3e943fb13)]
    for size in [0, 1, 2, 7, 8, 9, 15, 16, 17, 31, 32, 63, 64, 127, 128, 255, 256, 1024]:
        vectors.append((rng.randbytes(size), rng.getrandbits(64)))
    vectors.extend((rng.randbytes(rng.randrange(257)), rng.getrandbits(64))
                   for _ in range(80))
    for data, key in vectors:
        fixture.reset()
        fixture.uc.mem_write(DATA, data + b'\xa5' * 16)
        trace = fixture.run(0x2bc7b0, [DATA, len(data), key])
        expected = bytes(fixture.uc.mem_read(DATA, len(data) + 16))
        buffer = ctypes.create_string_buffer(data + b'\xa5' * 16)
        library.prism_xor_cycle64(buffer, len(data), key)
        ok = trace['reason'] == 'returned' and buffer.raw[:len(expected)] == expected
        case = {'kind': 'xor64', 'length': len(data), 'key': hex(key),
                'input_sha256': hashlib.sha256(data).hexdigest(),
                'passed': ok, 'trace': trace}
        cases.append(case)
        if not ok:
            failures.append(case)
    hex_vectors = [b'', bytes(range(256)), bytes.fromhex('000fa1ff')]
    hex_vectors.extend(rng.randbytes(rng.randrange(257)) for _ in range(32))
    for data in hex_vectors:
        for uppercase in [False, True]:
            fixture.reset()
            fixture.uc.mem_write(DATA, data or b'\x00')
            fixture.uc.mem_write(OUTPUT, b'\xa5' * (2 * len(data) + 16))
            trace = fixture.run(0x11da20, [OUTPUT, DATA, len(data), int(uppercase)])
            expected = bytes(fixture.uc.mem_read(OUTPUT, 2 * len(data) + 16))
            buffer = ctypes.create_string_buffer(b'\xa5' * (2 * len(data) + 16))
            source = ctypes.create_string_buffer(data)
            library.prism_hex_encode(buffer, source, len(data), uppercase)
            ok = trace['reason'] == 'returned' and buffer.raw[:len(expected)] == expected
            case = {'kind': 'hex', 'length': len(data), 'uppercase': uppercase,
                    'input_sha256': hashlib.sha256(data).hexdigest(),
                    'passed': ok, 'trace': trace}
            cases.append(case)
            if not ok:
                failures.append(case)
    result = {'scope': 'body output and 16 guard bytes; unmodified entry guards exercised',
              'excluded': ['ABI equivalence', 'return register of hex body',
                           'full-module behavior', 'concurrency', 'Android device execution'],
              'sample_sha256': hashlib.sha256((ROOT.parent / 'libprism-sun.so').read_bytes()).hexdigest(),
              'library_sha256': hashlib.sha256(library_path.read_bytes()).hexdigest(),
              'seed': '0x505249534d', 'total': len(cases),
              'passed': len(cases) - len(failures), 'failures': failures, 'cases': cases}
    (ROOT / 'evidence/differential_helpers.json').write_text(json.dumps(result, indent=2))
    print(json.dumps({key: result[key] for key in ['total', 'passed', 'failures']}), flush=True)
    return 1 if failures else 0


if __name__ == '__main__':
    raise SystemExit(main())
