"""Original ClientPropsChecker initializer/factory with registry insertion modeled."""
import json,struct
from device_fixture import *
from unicorn.arm64_const import UC_ARM64_REG_X2
f=DeviceFixture();f.reset();calls=[]
f.handlers[0x4ea8b8]=lambda f:f.return_value(DATA+0x1000)
def insert(f):
    key=f.uc.reg_read(UC_ARM64_REG_X1);callback=f.uc.reg_read(UC_ARM64_REG_X2)
    body=int.from_bytes(f.uc.mem_read(callback+32,8),'little');vt=int.from_bytes(f.uc.mem_read(body,8),'little')
    calls.append(dict(key=key,vtable=hex(vt),invoke=hex(int.from_bytes(f.uc.mem_read(vt+48,8),'little'))));f.return_value(0)
f.handlers[0x601c58]=insert
r=f.call(0x6fe530)
obs=dict(initializer=r,registrations=calls)
if r['reason']=='returned' and len(calls)==1:
    f.reset();f.uc.mem_write(DATA,struct.pack('<QQ',int(calls[0]['vtable'],16),0))
    q=f.call(int(calls[0]['invoke'],16),[DATA],DATA+0x8000);obs['factory']=q
    p=int.from_bytes(f.uc.mem_read(DATA+0x8000,8),'little');vt=int.from_bytes(f.uc.mem_read(p,8),'little');obs['checker_vtable']=hex(vt)
    obs['execute_slot']=hex(int.from_bytes(f.uc.mem_read(vt+64,8),'little'))
    f.reset();n=f.call(0x7144a0,[DATA],DATA+0x8000);obs['name_run']=n;obs['name']=f.get_string(DATA+0x8000).decode()
    f.reset();obs['task_id_run']=f.call(0x7149d8,[DATA])
(OUT/'evidence/registration-original.json').write_text(json.dumps(obs,indent=2));print(obs)
