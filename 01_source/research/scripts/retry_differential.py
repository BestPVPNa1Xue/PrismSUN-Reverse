"""Retry budget-limited XOR cases without repeating successful comparisons."""
import ctypes
import hashlib
import json
import random

from bounded_arm64 import Arm64Fixture, DATA, ROOT


def main():
    path = ROOT / 'evidence/differential_helpers.json'
    result = json.loads(path.read_text())
    library_path = ROOT / 'build/host/prism_helpers.dll'
    sample_path = ROOT.parent / 'libprism-sun.so'
    for source, field in [(library_path, 'library_sha256'),
                          (sample_path, 'sample_sha256')]:
        if hashlib.sha256(source.read_bytes()).hexdigest() != result[field]:
            raise RuntimeError(f'Changed artifact: {source}')
    pending = [case for case in result['failures']
               if case['kind'] == 'xor64'
               and case['trace']['reason'] == 'instruction_or_time_budget']
    if not pending:
        print('No budget-limited XOR cases remain', flush=True)
        return
    backup = ROOT / 'evidence/differential_initial.json'
    if not backup.exists():
        backup.write_text(json.dumps(result, indent=2))
    library = ctypes.CDLL(str(library_path))
    library.prism_xor_cycle64.argtypes = [ctypes.c_void_p, ctypes.c_size_t,
                                        ctypes.c_uint64]
    library.prism_xor_cycle64.restype = None
    rng = random.Random(int(result['seed'], 16))
    vectors = [(bytes.fromhex('75922f9dd65912a1'), 0xa12f2bb3e943fb13)]
    for size in [0, 1, 2, 7, 8, 9, 15, 16, 17, 31, 32, 63, 64,
                 127, 128, 255, 256, 1024]:
        vectors.append((rng.randbytes(size), rng.getrandbits(64)))
    vectors.extend((rng.randbytes(rng.randrange(257)), rng.getrandbits(64))
                   for _ in range(80))
    fixture = Arm64Fixture()
    for case in pending:
        data, key = next((data, key) for data, key in vectors
                         if hashlib.sha256(data).hexdigest() == case['input_sha256']
                         and hex(key) == case['key'])
        print(f"Retry XOR length={len(data)}, bounded at 10s/2M instructions", flush=True)
        fixture.reset()
        fixture.uc.mem_write(DATA, data + b'\xa5' * 16)
        trace = fixture.run(0x2bc7b0, [DATA, len(data), key],
                            count=2_000_000, timeout_us=10_000_000)
        expected = bytes(fixture.uc.mem_read(DATA, len(data) + 16))
        buffer = ctypes.create_string_buffer(data + b'\xa5' * 16)
        library.prism_xor_cycle64(buffer, len(data), key)
        case['attempts'] = [case['trace'], trace]
        case['trace'] = trace
        case['passed'] = trace['reason'] == 'returned' and buffer.raw[:len(expected)] == expected
        for original in result['cases']:
            if original['kind'] == case['kind'] and original['input_sha256'] == case['input_sha256']:
                original.update(case)
        print(json.dumps(case), flush=True)
    result['failures'] = [case for case in result['cases'] if not case['passed']]
    result['passed'] = result['total'] - len(result['failures'])
    path.write_text(json.dumps(result, indent=2))
    print(json.dumps({k: result[k] for k in ['total', 'passed', 'failures']}), flush=True)
    return 1 if result['failures'] else 0


if __name__ == '__main__':
    raise SystemExit(main())
