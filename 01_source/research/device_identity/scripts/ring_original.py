"""Original output-ring writer, inert memory only, including fragmentation/wrap."""
import json,struct
from device_fixture import *
if __name__=='__main__':
    f=DeviceFixture();rows=[]
    for index,(size,head,tail) in enumerate([(0,0,0),(1,0,0),(4088,0,0),(4089,15,15),(65408,0,0),(65409,0,0),(1,16,0),(1,0xffffffff,0xffffffff),(4089,15,0)]):
        f.reset();b=bytes(i%251 for i in range(size));f.put_string(DATA,b)
        f.uc.mem_write(0x7c06ac,struct.pack('<II',head,tail)+bytes(0x10000))
        r=f.call(0x591b70,[0x7c06ac,5,DATA])
        raw=bytes(f.uc.mem_read(0x7c06ac,0x10008));path=OUT/f'evidence/ring-{index}.bin';path.write_bytes(raw)
        row=dict(size=size,head=head,tail=tail,record_type=5,return_value=r['return'],run=r,output_file=path.name);rows.append(row)
        (OUT/'evidence/ring-original.json').write_text(json.dumps(rows,indent=2))
        print(index,size,head,tail,r['reason'],r['return'],raw[:16].hex(),flush=True)
