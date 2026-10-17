"""Bounded original-instruction digest probe. No Android process is launched."""
import json
import struct
import sys
import zlib
from pathlib import Path
from unicorn.arm64_const import UC_ARM64_REG_PC, UC_ARM64_REG_X0, UC_ARM64_REG_X1, UC_ARM64_REG_X30

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "accessibility" / "scripts"))
from hash_original import HashFixture
sys.path.insert(0, str(ROOT / "scripts"))
from bounded_arm64 import DATA

class DigestFixture(HashFixture):
    def __init__(self):
        super().__init__()
        self.callback_return = 0x3301fff0
        self.handlers[0x78ac20] = self.pthread_once
        self.handlers[self.callback_return] = self.finish_once
        self.once_return = 0
        self.once_log = []

    def reset(self):
        super().reset()
        self.once_return = 0
        self.once_log = []

    def pthread_once(self, _):
        once_ptr = self.uc.reg_read(UC_ARM64_REG_X0)
        callback = self.uc.reg_read(UC_ARM64_REG_X1)
        status = struct.unpack("<I", self.uc.mem_read(once_ptr, 4))[0]
        self.once_log.append({"once":hex(once_ptr),"callback":hex(callback),"status":status})
        if status:
            self.return_value(0)
            return
        self.uc.mem_write(once_ptr, struct.pack("<I", 1))
        self.once_return = self.uc.reg_read(UC_ARM64_REG_X30)
        self.uc.reg_write(UC_ARM64_REG_X30, self.callback_return)
        self.uc.reg_write(UC_ARM64_REG_PC, callback)

    def finish_once(self, _):
        self.uc.reg_write(UC_ARM64_REG_X30, self.once_return)
        self.return_value(0)

    def digest(self, data):
        self.reset()
        ptr=DATA+0x1000
        self.uc.mem_write(ptr, data or b"\0")
        result=self.run(0x44c740,[ptr,len(data)],count=3_000_000,timeout_us=30_000_000)
        result.update(data_hex=data.hex(),once=self.once_log,update_chunks_hex=self.updates,modeled_boundaries=sorted(self.modeled),algorithm_guess="CRC32")
        if result["reason"]=="returned":
            crc=zlib.crc32(data)
            result["expected"] = int.from_bytes(crc.to_bytes(4,"big"),"little")
            result["pass"] = result["return"]==result["expected"] and b"".join(bytes.fromhex(x) for x in self.updates)==data
        else:
            result["pass"]=False
        return result

if __name__=="__main__":
    fixture=DigestFixture()
    cases=[b"",b"a",b"abc",b"123456789",bytes(range(32)),b"\0"*1024]
    results=[fixture.digest(x) for x in cases]
    out={"sample_sha256":"92e7d4adda7e222aa9dce389009a186adabb2602b80d618d417e0f6d509adaf4","entry":"0x44c740","scope":"Original digest function/Botan path; TLS, allocator and pthread_once modeled; all unspecified imports/syscalls blocked.","result":"PASS" if all(x["pass"] for x in results) else "FAIL","cases":results}
    target=Path(__file__).resolve().parents[1]/"evidence"/"digest-differential.json"
    target.write_text(json.dumps(out,indent=2),encoding="utf-8")
    print(out["result"],[(x["data_hex"][:8],x["reason"],x["steps"],x.get("return"),x.get("expected")) for x in results])
    sys.exit(0 if out["result"]=="PASS" else 1)
