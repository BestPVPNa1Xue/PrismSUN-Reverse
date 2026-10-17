"""Confirm the digest-name decoder using unmodified AArch64 instructions."""
import json

from bounded_arm64 import Arm64Fixture, DATA, ROOT


def main():
    raw = bytes.fromhex('1f25bbb6fb331b16')
    masks = bytes.fromhex('8342050e243f6ee7')
    intermediate = bytes(a ^ b for a, b in zip(raw, masks))
    fixture = Arm64Fixture()
    cases = []
    for flag in [1, 3, 0]:
        fixture.reset()
        fixture.uc.mem_write(DATA, intermediate + bytes([flag]) + b'\xa5' * 16)
        trace = fixture.run(0x5c433c, [DATA], count=100000, timeout_us=2_000_000)
        observed = bytes(fixture.uc.mem_read(DATA, 25))
        expected = (b'SHA-256\x00\x00' if flag & 1 else intermediate + b'\x00')
        expected += b'\xa5' * 16
        passed = trace['reason'] == 'returned' and observed == expected
        cases.append({'flag': flag, 'passed': passed, 'trace': trace,
                      'observed': observed.hex(), 'expected': expected.hex()})
        print(json.dumps({'flag': flag, 'passed': passed, 'trace': trace}), flush=True)
    result = {'scope': 'digest-name decoder only; no JNI or digest body execution',
              'raw_source': '0x7af3cc', 'raw': raw.hex(), 'masks': masks.hex(),
              'intermediate': intermediate.hex(), 'decoder': '0x5c433c',
              'key': '0xf14339ed95ff2fcf', 'algorithm': 'SHA-256',
              'total': len(cases), 'passed': sum(case['passed'] for case in cases),
              'cases': cases}
    (ROOT / 'evidence/digest_decode_emulation.json').write_text(
        json.dumps(result, indent=2), encoding='utf-8')
    return 0 if result['passed'] == result['total'] else 1


if __name__ == '__main__':
    raise SystemExit(main())
