"""Original collectors with synthetic NDK and file callbacks; no host/device reads."""
import hashlib,json,struct
from device_fixture import *
from unicorn.arm64_const import UC_ARM64_REG_X3
SALT=bytes.fromhex('67d6d31dcea9eec7ba1b1ce2c87bab7b')
class Collectors(DeviceFixture):
    def __init__(self):
        super().__init__()
        self.handlers[0x56bfb4]=lambda f:f.return_value(DATA+0x1000)
        self.handlers[0x5b6ff4]=lambda f:f.return_value(DATA)
        self.handlers[DATA+0x1800]=self.create
        self.handlers[DATA+0x1804]=self.property
        self.handlers[DATA+0x1808]=self.release
        self.handlers[0x5cee84]=self.open
        self.handlers[0x5d8194]=self.read
        self.handlers[0x5d5a04]=self.close
    def create(self,_):
        p=self.uc.reg_read(UC_ARM64_REG_X0)
        self.trace.append(dict(api='createByUUID',uuid=bytes(self.uc.mem_read(p,16)).hex()))
        self.return_value(DATA+0x1700)
    def property(self,_):
        p=self.uc.reg_read(UC_ARM64_REG_X1);out=self.uc.reg_read(UC_ARM64_REG_X2)
        self.trace.append(dict(api='getPropertyByteArray',name=self.cstring(p).decode(),status=self.status))
        self.uc.mem_write(DATA+0x1900,self.raw)
        self.uc.mem_write(out,struct.pack('<QQ',DATA+0x1900,len(self.raw)))
        self.return_value(self.status)
    def release(self,_):
        self.trace.append(dict(api='release',handle=hex(self.uc.reg_read(UC_ARM64_REG_X0))))
        self.return_value(0)
    def open(self,_):
        self.trace.append(dict(api='open',path=self.cstring(self.uc.reg_read(UC_ARM64_REG_X0)).decode(),flags=self.uc.reg_read(UC_ARM64_REG_X1)))
        self.return_value(self.fd)
    def read(self,_):
        fd=self.uc.reg_read(UC_ARM64_REG_X0);p=self.uc.reg_read(UC_ARM64_REG_X1);n=self.uc.reg_read(UC_ARM64_REG_X2)
        v=self.raw[:n];self.uc.mem_write(p,v)
        self.trace.append(dict(api='read',fd=fd,count=n,result=-1 if self.read_error else len(v)))
        self.return_value(-1 if self.read_error else len(v))
    def close(self,_):
        self.trace.append(dict(api='close',fd=self.uc.reg_read(UC_ARM64_REG_X0)));self.return_value(0)
    def probe(self,source,raw,available=True,disabled=False,status=0,fd=17,read_error=False):
        self.reset();self.trace=[];self.raw=raw;self.status=status;self.fd=fd;self.read_error=read_error
        self.uc.mem_write(DATA+217,bytes([disabled]))
        self.uc.mem_write(DATA+0x1000,struct.pack('<QQQQ',int(available),DATA+0x1800,DATA+0x1804,DATA+0x1808))
        r=self.call(0x4df3c8 if source=='drm' else 0x4dfc3c,output=DATA+0x2000)
        value=self.get_string(DATA+0x2000).decode() if r['reason']=='returned' else None
        base=(raw.hex().upper().encode() if source=='drm' and available and not disabled and status==0 else b'') if source=='drm' else (raw[:47].split(b'\0',1)[0].rstrip(b'\r\n') if fd>=0 and not read_error else b'')
        expected=hashlib.sha256(base+SALT).hexdigest().upper() if base else ''
        return dict(source=source,raw_hex=raw.hex(),available=available,disabled=disabled,status=status,fd=fd,read_error=read_error,trace=self.trace,value=value,expected=expected,pass_=value==expected,run=r,modeled_boundaries=sorted(self.modeled|{'NDK_DRM_callbacks','context_getter','DRM_loader_getter','open/read/close_wrappers'}))
if __name__=='__main__':
    f=Collectors();rows=[]
    cases=[dict(source='drm',raw=b'\0\x01\xfe\xff'),dict(source='drm',raw=b''),dict(source='drm',raw=b'abc',status=-1),dict(source='drm',raw=b'abc',available=False),dict(source='drm',raw=b'abc',disabled=True)]
    cases += [dict(source='boot',raw=x) for x in [b'12345678-1234-1234-1234-123456789012\n',b'abc\r\n\n',b'',b'\r\n',b'abc\0tail',b'x'*60]]
    cases += [dict(source='boot',raw=b'abc',fd=-1),dict(source='boot',raw=b'abc',read_error=True)]
    for case in cases:
        r=f.probe(**case);rows.append(r);print(case,r['run']['reason'],r['value'],r['pass_'],r['trace'],flush=True)
        (OUT/'evidence/collectors-original.json').write_text(json.dumps(rows,indent=2))
        if r['run']['reason']!='returned':break
