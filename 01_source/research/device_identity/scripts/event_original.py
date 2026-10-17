"""Original event-19 consumer; platform collection values are explicit fixtures."""
import json,struct
from device_fixture import *
OUTPUT=DATA+0x1800
class EventFixture(DeviceFixture):
    def __init__(self):
        super().__init__()
        self.handlers[0x3b8c40]=lambda f:f.return_value(DATA)
        self.handlers[0x4df3c8]=lambda f:f.output_string(self.primary)
        self.handlers[0x4dfc3c]=lambda f:f.output_string(self.fallback)
        self.handlers[0x306df0]=lambda f:f.return_value(0)
        self.handlers[0x6ae7d0]=lambda f:f.return_value(self.env_ok)
        self.handlers[0x6b0660]=lambda f:f.return_value(DATA+0x1700)
        self.handlers[0x3078cc]=lambda f:f.return_value(0)
        self.handlers[0x37843c]=lambda f:f.output_string(b'TEST_APK_DIGEST')
        self.handlers[0x2e5c18]=lambda f:f.output_string(b'APP_PACKAGE')
        self.handlers[0x37fb88]=self.activities
    def output_string(self,value):
        out=self.uc.reg_read(UC_ARM64_REG_X8);self.put_string(out,value);self.return_value(out)
    def activities(self,_):
        out=self.uc.reg_read(UC_ARM64_REG_X8);self.put_string(out,b'TARGET_ACTIVITY')
        self.uc.mem_write(out+24,b'\x01');self.return_value(out)
    def cjson(self,ptr,depth=0):
        assert depth<16
        if not ptr:return None
        b=bytes(self.uc.mem_read(ptr,64));typ=struct.unpack_from('<I',b,24)[0]&255
        if typ==16:return self.cstring(struct.unpack_from('<Q',b,32)[0]).decode('utf8','replace')
        if typ==1:return False
        if typ==2:return True
        if typ==4:return None
        if typ==8:return struct.unpack_from('<d',b,48)[0]
        if typ==32:
            ch=struct.unpack_from('<Q',b,16)[0];res=[]
            while ch:
                assert len(res)<100
                res.append(self.cjson(ch,depth+1));ch=struct.unpack('<Q',self.uc.mem_read(ch,8))[0]
            return res
        raise ValueError((hex(ptr),typ))
    def consume(self,challenge=b'CHALLENGE',primary=b'DEVICE_ID',fallback=b'BOOT_ID',env_ok=True,ready=1,item_count=1,item_type=16,container_type=32):
        self.reset();self.primary=primary;self.fallback=fallback;self.env_ok=env_ok
        self.put_vector(DATA+592,b'TEST_KEY');self.uc.mem_write(DATA+616,struct.pack('<H',ready))
        root=self.allocate(64);child=self.allocate(64);txt=self.allocate(len(challenge)+1)
        self.uc.mem_write(txt,challenge+b'\0')
        self.uc.mem_write(root+16,struct.pack('<Q',child if item_count else 0));self.uc.mem_write(root+24,struct.pack('<I',container_type))
        self.uc.mem_write(child+24,struct.pack('<I',item_type));self.uc.mem_write(child+32,struct.pack('<Q',txt))
        for _ in range(1,item_count):
            other=self.allocate(64);self.uc.mem_write(child,struct.pack('<Q',other))
            self.uc.mem_write(other+24,struct.pack('<I',item_type));self.uc.mem_write(other+32,struct.pack('<Q',txt));child=other
        self.uc.mem_write(DATA+0x800,struct.pack('<Q',root));self.uc.mem_write(OUTPUT,bytes([0xcc])*40)
        r=self.call(0x7153a8,[0,DATA+0x800],OUTPUT)
        raw=bytes(self.uc.mem_read(OUTPUT,24))
        kind=int.from_bytes(raw[:4],'little')
        obs=dict(kind=kind,event_type=raw[4],error=int.from_bytes(raw[16:20],'little'),guard_ok=bytes(self.uc.mem_read(OUTPUT+24,16))==b'\xcc'*16)
        if r['reason']=='returned' and kind==0:obs['payload']=self.cjson(int.from_bytes(raw[8:16],'little'))
        return dict(inputs=dict(challenge=challenge.decode(),primary=primary.decode(),fallback=fallback.decode(),env_ok=env_ok,ready=ready,item_count=item_count,item_type=item_type,container_type=container_type),observation=obs,run=r,modeled_boundaries=sorted(self.modeled|{'singleton','platform_id_values','JNI_scope','APK_digest','package_name','activity_result'}))

if __name__=='__main__':
    f=EventFixture();rows=[]
    for kwargs in [{},{'primary':b''},{'primary':b'','fallback':b''},{'challenge':b'SHORT'},{'env_ok':False},{'ready':0}]:
        r=f.consume(**kwargs);rows.append(r);print(r['inputs'],r['run']['reason'],r['observation'],flush=True)
        (OUT/'evidence/event-original.json').write_text(json.dumps(rows,indent=2))
        if r['run']['reason']!='returned':break
