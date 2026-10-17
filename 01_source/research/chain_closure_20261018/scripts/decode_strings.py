"""Static arithmetic from saved IDA expressions; never executes sample code."""
import json
from pathlib import Path

out = []
def decode(label, src, masks, key, evidence):
    s, m = bytes.fromhex(src), bytes.fromhex(masks)
    k = key.to_bytes(8, 'little')
    first = bytes(x ^ y for x, y in zip(s, m))
    result = bytes(x ^ k[i % 8] for i, x in enumerate(first))
    out.append(dict(label=label, source=s.hex(), xor_masks=m.hex(),
                    key_little_endian=k.hex(), first=first.hex(),
                    result=result.decode('ascii'), evidence=evidence))
    print(label, repr(result))

decode('maps_suffix', '6d 53 7f 51 26 6d', '1f 9b 31 fe f0 be',
       0xDB63D3A5DF2FA55D, ['0x5cd0e4', '0x5f50ac'])
decode('excluded_marker', 'e8 2d 0c f2 70 a5 35 64 f2 e2',
       '0f 66 96 0b f8 e8 13 f1 14 cd', 0xF14339ED95FF2FCF,
       ['0x5cdc88', '0x5f5634'])
decode('maps_format',
       'f7 55 fe 38 e0 e6 48 1c 2b 55 a4 87 00 34 06 aa 14 01 45 83 fc 8f e1 aa 10 d4 07 ed 2f 75 e5 81',
       '2b a0 59 12 f2 b9 57 15 f7 f8 08 a0 12 6b 19 a3 c8 e0 a0 a1 b3 9c a3 ef 9c 6d fd 84 3d 6c f1 a8',
       0x2967333707DF99F9, ['0x5cf3cc', '0x5f5bf0'])
decode('fdopen_mode', '6f 19', 'd0 40', 0x810979618F4359CD,
       ['0x5d0c44', '0x5f611c'])
decode('proc_prefix', 'b8 61 95 d9 b0 2a b1', 'd2 98 20 65 a0 4c d8',
       0x5F694973D3C78945, ['0x5fedc0', '0x600f70'])
dest = Path(__file__).resolve().parents[1] / 'evidence/string-static-decode.json'
dest.write_text(json.dumps(out, indent=2), encoding='utf-8')
