"""Compare compiled C++ to independent CRC and original consumer instructions."""
import ctypes as C
import json
import os
import random
import sys
import zlib
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
from consumer_original import ConsumerFixture

dll_search = os.add_dll_directory('D:/msys64/ucrt64/bin')
lib = C.CDLL(str(ROOT / 'build/host/accessibility_core.dll'))

class Bytes(C.Structure):
    _fields_ = [('data', C.c_void_p), ('size', C.c_size_t)]
class ModelResult(C.Structure):
    _fields_ = [(n, C.c_uint32) for n in ['kind', 'event_type', 'error_code', 'previous_hash', 'initialized']]

lib.a11y_snapshot_hash.argtypes = [C.POINTER(Bytes), C.c_size_t]
lib.a11y_snapshot_hash.restype = C.c_uint32
lib.a11y_evaluate.argtypes = [C.c_uint32, C.c_uint32, C.POINTER(Bytes), C.c_size_t, C.c_int,
                            C.POINTER(ModelResult), C.c_void_p, C.c_size_t]
lib.a11y_evaluate.restype = C.c_int

def packed(names):
    keep = [C.create_string_buffer(n) for n in names]
    args = (Bytes * len(names))(*(Bytes(C.cast(b, C.c_void_p), len(n)) for b, n in zip(keep, names)))
    return args, keep

def reference_hash(names):
    crc = zlib.crc32(b''.join(n + b'\0' for n in sorted(names)))
    return int.from_bytes(crc.to_bytes(4, 'big'), 'little')

def model(names, initialized, previous_hash, env):
    args, keep = packed(names)
    out, payload = ModelResult(), C.create_string_buffer(131072)
    rc = lib.a11y_evaluate(previous_hash, initialized, args, len(names), env, C.byref(out), payload, len(payload))
    assert rc == 0, rc
    values = {n: getattr(out, n) for n, _ in out._fields_}
    # latin-1 lets us compare cJSON raw byte strings, including MUTF-8, without
    # accidentally normalizing invalid UTF-8 into a different representation.
    parsed = json.loads(payload.value.decode('latin-1'))
    values['payload_hex'] = [] if parsed is None else [n.encode('latin-1').hex() for n in parsed]
    return values

def main():
    if '--replay' in sys.argv:
        result = json.loads((ROOT/'evidence/core-differential.json').read_text())
        for check in result['hash_checks']:
            names = [bytes.fromhex(n) for n in check['input_hex']]
            args, keep = packed(names)
            assert lib.a11y_snapshot_hash(args, len(names)) == check['expected']
        for case in result['cases']:
            names = [bytes.fromhex(n) for n in case['original']['input_hex']]
            before = case['before']
            actual = model(names, before['initialized'], before['previous_hash'], before['env_available'])
            assert all(case['original']['observation'][k] == v for k, v in actual.items())
        original_hash = json.loads((ROOT/'evidence/hash-differential.json').read_text())
        for case in original_hash['cases']:
            names = [bytes.fromhex(n) for n in case['input_hex']]
            args, keep = packed(names)
            assert lib.a11y_snapshot_hash(args, len(names)) == case['return']
        import hashlib
        verified = {'result': 'PASS', 'hash_cases': len(result['hash_checks']), 'original_hash_cases': len(original_hash['cases']), 'consumer_cases': len(result['cases']),
                    'mode': 'Final compiled DLL replay against retained original-instruction observations',
                    'dll_sha256': hashlib.sha256((ROOT/'build/host/accessibility_core.dll').read_bytes()).hexdigest(),
                    'original_evidence_sha256': hashlib.sha256((ROOT/'evidence/core-differential.json').read_bytes()).hexdigest()}
        (ROOT/'evidence/core-final-replay.json').write_text(json.dumps(verified, indent=2))
        print(json.dumps(verified))
        return
    rng = random.Random(0xa11ce)
    vectors = [[], [b''], [b'', b''], [b'z', b'a'], [b'a', b'z'], [b'a', b'a'],
               [b'a\0b', b'a'], [b'\xff', b'\x80', b'\x7f'], [b'\xc0\x80', b''],
               [b'TARGET/.KeyMapperService', b'TARGET/.TalkBackService'],
               [b'"\\\t\n\r\x01'], [b'x'*22, b'x'*23, b'x'*64]]
    vectors += [[rng.randbytes(rng.randrange(0, 80)) for _ in range(rng.randrange(0, 10))] for _ in range(24)]
    hash_evidence = json.loads((ROOT / 'evidence/hash-differential.json').read_text())
    # Independently generated vectors plus every retained original hash case.
    old = hash_evidence.get('cases', hash_evidence.get('results', []))
    for item in old:
        raw = item.get('input_hex') or item.get('original', {}).get('input_hex')
        if raw is not None: vectors.append([bytes.fromhex(n) for n in raw])
    hash_checks = []
    for names in vectors:
        args, keep = packed(names)
        actual, expected = lib.a11y_snapshot_hash(args, len(names)), reference_hash(names)
        assert actual == expected, (names, actual, expected)
        hash_checks.append({'input_hex': [n.hex() for n in names], 'actual': actual, 'expected': expected, 'passed': True})
    fixture = ConsumerFixture()
    cases = []
    # Independent pre-state combinations ensure first/equal/changed/error paths
    # are all exercised, even when the current hash is zero.
    for names in vectors[:36]:
        crc = reference_hash(names)
        for initialized, previous, env in [(False, 0x12345678, True), (True, crc, True),
                                            (True, crc ^ 0x80000000, True),
                                            (False, crc, False), (True, crc, False)]:
            original = fixture.consume(names, initialized, previous, env)
            expected = model(names, initialized, previous, env)
            observed = original['observation']
            ok = original['reason'] == 'returned' and observed['guard_unchanged'] and all(observed[k] == v for k, v in expected.items())
            cases.append({'before': {'initialized': initialized, 'previous_hash': previous, 'env_available': env},
                          'original': original, 'compiled_cpp': expected, 'passed': ok})
            if not ok:
                (ROOT/'evidence/core-differential-failure.json').write_text(json.dumps(cases[-1], indent=2))
                raise AssertionError((original['reason'], observed, expected))
        print(f'consumer vectors {len(cases)}/180', flush=True)
    result = {'scope': 'Original consumer, cJSON, atomics, CRC and result constructors vs compiled C++; JNI IDs and runtime boundaries explicitly modeled',
              'hash_passed': len(hash_checks), 'consumer_passed': len(cases), 'failed': 0,
              'hash_checks': hash_checks, 'cases': cases}
    (ROOT/'evidence/core-differential.json').write_text(json.dumps(result, indent=2))
    print(json.dumps({k: result[k] for k in ['hash_passed', 'consumer_passed', 'failed']}))

if __name__ == '__main__':
    main()
