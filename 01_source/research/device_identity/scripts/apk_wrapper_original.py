"""Original wrapper's path and file-size gates, using synthetic metadata."""
import json,struct
from device_fixture import *
class Wrapper(DeviceFixture):
    def __init__(self):
        super().__init__()
        self.handlers[0x2e8e80]=lambda f:f.out(self.path)
        self.handlers[0x37b87c]=lambda f:f.return_value(17)
        self.handlers[0x37c8ec]=self.stat
        self.handlers[0x37cdf8]=lambda f:f.return_value(0)
        self.handlers[0x4c0718]=lambda f:f.out(b'TEST_CERTIFICATE_DER')
    def out(self,v):
        self.put_string(self.uc.reg_read(UC_ARM64_REG_X8),v);self.return_value(0)
    def stat(self,_):
        p=self.uc.reg_read(UC_ARM64_REG_X1);self.uc.mem_write(p+48,struct.pack('<Q',self.size));self.return_value(0)
    def probe(self,path,size):
        self.reset();self.path=path;self.size=size
        r=self.call(0x37843c,[0],DATA+0x1000)
        return dict(path=path.decode(),size=size,value=self.get_string(DATA+0x1000).decode() if r['reason']=='returned' else None,run=r,modeled_boundaries=sorted(self.modeled|{'sourceDir','openat','stat','close','certificate_extraction'}))
if __name__=='__main__':
    f=Wrapper();rows=[]
    for p,s in [(b'',100),(b'TARGET.apk',1<<30),(b'/data/app/TARGET/base.apk',100),(b'/data/app/TARGET/base.apk',1<<30),(b'prefix/data/app/TARGET/base.apk',1<<30)]:
        r=f.probe(p,s);rows.append(r);print(p,s,r['value'],r['run']['reason'],flush=True)
        (OUT/'evidence/apk-wrapper-original.json').write_text(json.dumps(rows,indent=2))
