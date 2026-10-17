"""Verify the decoded original CRC table and state convention."""
import hashlib
import json
import struct
from hash_original import HashFixture, ROOT, UC_ARM64_REG_X0


class ObserveCRC(HashFixture):
    def __init__(self):
        super().__init__()
        self.states = []

    def _hook(self, uc, address, size, user_data):
        if address in (0x1053A8, 0x106128):
            obj = uc.reg_read(UC_ARM64_REG_X0)
            state = struct.unpack("<I", uc.mem_read(obj + 8, 4))[0]
            self.states.append({"address": hex(address), "state": f"0x{state:08x}"})
        super()._hook(uc, address, size, user_data)


fixture = ObserveCRC()
result = fixture.hash([b"a", b"z"])
observed = bytes(fixture.uc.mem_read(0x7A88A0, 1024))
table = []
for value in range(256):
    for _ in range(8):
        value = (value >> 1) ^ (0xEDB88320 if value & 1 else 0)
    table.append(value)
expected = struct.pack("<256I", *table)
evidence = {
    "entry": "0x6d4374", "result": result,
    "table_address": "0x7a88a0", "table_sha256": hashlib.sha256(observed).hexdigest(),
    "polynomial_reflected": "0xedb88320", "table_count": 256,
    "all_entries_match": observed == expected, "states": fixture.states,
    "observed_table": [f"0x{value:08x}" for value in struct.unpack("<256I", observed)],
}
assert result["reason"] == "returned"
assert observed == expected
assert fixture.states[0]["state"] == "0xffffffff"
(ROOT / "evidence" / "hash-crc-table.json").write_text(json.dumps(evidence, indent=2), encoding="utf-8")
print("PASS: all 256 decoded CRC32/IEEE table entries and initial state match")
