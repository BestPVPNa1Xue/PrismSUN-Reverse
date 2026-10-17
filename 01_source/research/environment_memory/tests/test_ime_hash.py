"""Bounded IME-list hash differential against original ARM64 instructions."""
import json
import struct
import sys
import zlib
from pathlib import Path
ROOT=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(Path(__file__).resolve().parent))
from test_integrity_digest import DigestFixture
sys.path.insert(0,str(ROOT/"scripts"))
from bounded_arm64 import DATA

class ImeFixture(DigestFixture):
    def hash_names(self,names):
        self.reset()
        array=self.allocate(24*len(names))
        for i,name in enumerate(names):
            if len(name)<=22:
                obj=bytes([len(name)*2])+name+bytes(23-len(name))
            else:
                ptr=self.allocate(len(name)+1)
                self.uc.mem_write(ptr,name+b"\0")
                obj=struct.pack('<QQQ',(len(name)+16)|1,len(name),ptr)
            self.uc.mem_write(array+24*i,obj)
        self.uc.mem_write(DATA,struct.pack('<QQQ',array,array+24*len(names),array+24*len(names)))
        got=self.run(0x6f8da4,[DATA],count=2_000_000,timeout_us=45_000_000)
        expected=int.from_bytes(zlib.crc32(b''.join(x+b'\0' for x in sorted(names))).to_bytes(4,'big'),'little')
        sorted_original=[]
        for i in range(len(names)):
            obj=bytes(self.uc.mem_read(array+24*i,24))
            if obj[0]&1:
                _,size,ptr=struct.unpack('<QQQ',obj)
                sorted_original.append(bytes(self.uc.mem_read(ptr,size)))
            else:sorted_original.append(obj[1:1+obj[0]//2])
        got.update(input_hex=[x.hex() for x in names],sorted_hex=[x.hex() for x in sorted_original],update_chunks_hex=self.updates,expected=expected,pass_result=got['reason']=='returned' and got['return']==expected and sorted_original==sorted(names) and b''.join(bytes.fromhex(x) for x in self.updates)==b''.join(x+b'\0' for x in sorted(names)))
        return got

if __name__=='__main__':
    cases=[[],[b'a'],[b'b',b'a'],[b'a',b'b'],[b'a',b'a'],[b'z'*23,b'z'*22,b'a'*24],[b'com.example.IME',b'com.example.Other'],[b'\xff',b'\x80',b'\x7f'],[b'a\x00b']]
    fixture=ImeFixture(); results=[fixture.hash_names(x) for x in cases]
    out={'sample_sha256':'92e7d4adda7e222aa9dce389009a186adabb2602b80d618d417e0f6d509adaf4','entry':'0x6f8da4','oracle':'zlib.crc32(sorted NUL-terminated service-name bytes), bswap32','scope':'Original IME hash function and Botan path run in bounded ARM64 fixture; allocators/TLS modeled.','passed':sum(x['pass_result'] for x in results),'count':len(results),'cases':results}
    (Path(__file__).resolve().parents[1]/'evidence'/'ime-hash-differential.json').write_text(json.dumps(out,indent=2),encoding='utf-8')
    print('PASS' if out['passed']==out['count'] else 'FAIL',out['passed'],'/',out['count'])
    for x in results: print(x['input_hex'],x['reason'],x['steps'],x['return'],x['expected'])
    sys.exit(0 if out['passed']==out['count'] else 1)
