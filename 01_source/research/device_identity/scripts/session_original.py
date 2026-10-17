"""Run only the original session installer and scalar getters; inputs are synthetic."""
import json, struct
from device_fixture import DeviceFixture, DATA, OUT

f = DeviceFixture()
rows = []
for generation, aes, mac in [(1, bytes(range(32)), b'TEST_KEY'),
                              (65535, b'\xA5' * 32, b''),
                              (0, b'A', b'TEST_MAC')]:
    f.reset()
    f.put_vector(DATA + 568, b'OLD_AES')
    f.put_vector(DATA + 592, b'OLD_MAC')
    f.uc.mem_write(DATA + 616, struct.pack('<H', 7))
    f.uc.mem_write(DATA + 624, struct.pack('<Q', 123456))
    f.put_vector(DATA + 0x800, aes)
    f.put_vector(DATA + 0x900, mac)
    run = f.call(0x5b77d8, [DATA, DATA + 0x800, DATA + 0x900, generation])
    actual = dict(aes_hex=f.get_vector(DATA + 568).hex(),
                  hmac_hex=f.get_vector(DATA + 592).hex(),
                  generation=struct.unpack('<H', f.uc.mem_read(DATA + 616, 2))[0],
                  next_sequence=struct.unpack('<Q', f.uc.mem_read(DATA + 624, 8))[0])
    expected = dict(aes_hex=aes.hex(), hmac_hex=mac.hex(),
                    generation=generation, next_sequence=0)
    ready = f.call(0x4d92b4, [DATA])
    gen_getter = f.call(0x4d1f14, [DATA])
    first_seq = f.call(0x596b58, [DATA])
    after_seq = struct.unpack('<Q', f.uc.mem_read(DATA + 624, 8))[0]
    ok = run['reason'] == 'returned' and actual == expected
    ok = ok and all(x['reason'] == 'returned' for x in (ready, gen_getter, first_seq))
    ok = ok and ready['return'] == int(generation != 0) and gen_getter['return'] == generation
    ok = ok and first_seq['return'] == 0 and after_seq == 1
    rows.append(dict(inputs=expected, actual=actual, installer_run=run,
                     ready_run=ready, generation_run=gen_getter, sequence_run=first_seq,
                     sequence_after_getter=after_seq, pass_=ok,
                     modeled_boundaries=sorted(f.modeled)))
    print('session', generation, run['reason'], 'PASS' if ok else 'FAIL', flush=True)
    (OUT / 'evidence/session-original.json').write_text(json.dumps(rows, indent=2))
    if not ok:
        raise SystemExit(1)
