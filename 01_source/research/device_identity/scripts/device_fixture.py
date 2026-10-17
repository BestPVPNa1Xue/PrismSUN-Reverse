"""Execute source-bound ARM64 logic with inert allocator/libc/TLS fixtures."""
import json, struct, sys
from pathlib import Path
ROOT=Path(__file__).resolve().parents[3]
sys.path.insert(0,str(ROOT/'research/accessibility/scripts'))
from hash_original import HashFixture, DATA, SENTINEL
from unicorn.arm64_const import UC_ARM64_REG_X0, UC_ARM64_REG_X1, UC_ARM64_REG_X2, UC_ARM64_REG_X8, UC_ARM64_REG_X30
OUT=ROOT/'research/device_identity'
class DeviceFixture(HashFixture):
    def __init__(self):
        super().__init__()
        for address,name in self.imports.items():
            if name in ('pthread_mutex_lock','pthread_mutex_unlock','pthread_cond_broadcast','getauxval','getenv'):
                self.handlers[address]=lambda f,n=name: f.modeled_zero(n)
            elif name=='posix_memalign': self.handlers[address]=self.aligned_alloc
            elif name=='syscall': self.handlers[address]=self.libc_syscall
            elif name=='strcpy': self.handlers[address]=self.strcpy
    def strcpy(self,_):
        dst=self.uc.reg_read(UC_ARM64_REG_X0);src=self.uc.reg_read(UC_ARM64_REG_X1)
        self.uc.mem_write(dst,self.cstring(src)+b'\0');self.modeled.add('strcpy');self.return_value(dst)
    def libc_syscall(self,_):
        nr=self.uc.reg_read(UC_ARM64_REG_X0)
        if nr==178:
            self.modeled.add('syscall_gettid:synthetic_1');self.return_value(1)
        else:
            self.reason='blocked_libc_syscall:'+str(nr);self.uc.emu_stop()
    def modeled_zero(self,name):
        self.modeled.add(name+':single_thread_or_no_hwcap');self.return_value(0)
    def aligned_alloc(self,_):
        p=self.uc.reg_read(UC_ARM64_REG_X0);align=self.uc.reg_read(UC_ARM64_REG_X1);n=self.uc.reg_read(UC_ARM64_REG_X2)
        assert align and not align&(align-1)
        self.next=(self.next+align-1)&~(align-1)
        self.uc.mem_write(p,struct.pack('<Q',self.allocate(n)));self.modeled.add('posix_memalign');self.return_value(0)
    def put_string(self,where,value):
        if len(value)<=22:self.uc.mem_write(where,bytes([len(value)*2])+value+bytes(23-len(value)))
        else:
            p=self.allocate(len(value)+1);self.uc.mem_write(p,value+b'\0')
            self.uc.mem_write(where,struct.pack('<QQQ',((len(value)+16)&~15)|1,len(value),p))
    def get_string(self,where):
        b=bytes(self.uc.mem_read(where,24))
        if b[0]&1:
            _,n,p=struct.unpack('<QQQ',b);assert n<100000;return bytes(self.uc.mem_read(p,n))
        n=b[0]>>1;assert n<=22;return b[1:1+n]
    def put_vector(self,where,value):
        p=self.allocate(len(value));self.uc.mem_write(p,value)
        self.uc.mem_write(where,struct.pack('<QQQ',p,p+len(value),p+len(value)))
    def get_vector(self,where):
        start,end,_=struct.unpack('<QQQ',self.uc.mem_read(where,24));assert 0<=end-start<100000
        return bytes(self.uc.mem_read(start,end-start))
    def call(self,entry,args=(),output=None):
        self.uc.reg_write(UC_ARM64_REG_X30,SENTINEL)
        if output is not None:self.uc.reg_write(UC_ARM64_REG_X8,output)
        r=self.run(entry,args,count=4000000,timeout_us=40000000)
        if r['reason']!='returned':
            r['last_args']=[hex(self.uc.reg_read(x)) for x in (UC_ARM64_REG_X0,UC_ARM64_REG_X1,UC_ARM64_REG_X2,UC_ARM64_REG_X8,UC_ARM64_REG_X30)]
        return r

def constants():
    f=DeviceFixture();rows=[]
    for writer,decoder in [(0x5d8e44,0x5da398),(0x5ba690,0x5bb4ac),(0x718418,0x719668)]:
        f.reset();r=f.call(writer,[DATA]);p=r['return']
        if r['reason']!='returned':rows.append(dict(writer=hex(writer),run=r));continue
        q=f.call(decoder,[p]);b=f.cstring(q['return']) if q['reason']=='returned' else b''
        rows.append(dict(writer=hex(writer),decoder=hex(decoder),writer_run=r,decoder_run=q,bytes=b.hex(),text=b.decode('utf8','replace')))
    (OUT/'evidence/constants-original.json').write_text(json.dumps(rows,indent=2))
    for r in rows:print(r.get('writer'),r.get('text'),r.get('run',{}).get('reason'),r.get('decoder_run',{}).get('reason'))

def digest_probe():
    import hashlib,hmac
    f=DeviceFixture(); rows=[]
    salt=bytes.fromhex('67d6d31dcea9eec7ba1b1ce2c87bab7b')
    for v in [b'',b'00',b'0001FEFF',b'abc',bytes(range(64))]:
        f.reset();f.put_vector(DATA,v)
        r=f.call(0x5b9df4,[DATA],DATA+0x100)
        actual=f.get_vector(DATA+0x100) if r['reason']=='returned' else b''
        expected=hashlib.sha256(v+salt).digest()
        rows.append(dict(input=v.hex(),actual=actual.hex(),expected=expected.hex(),pass_=actual==expected,run=r,updates=f.updates,vtable=f.vtable))
        print('digest',len(v),r['reason'],actual.hex(),actual==expected)
    for key,msg in [(b'TEST_KEY',b'DEVICECHALLENGECLIENT'),(b'',b''),(bytes(range(80)),b'a'*65)]:
        f.reset(); f.put_vector(DATA,key);f.put_string(DATA+0x100,msg)
        r=f.call(0x5ba370,[DATA,DATA+0x100],DATA+0x200)
        actual=f.get_string(DATA+0x200) if r['reason']=='returned' else b''
        expected=hmac.new(key,msg,hashlib.sha256).hexdigest().upper().encode()
        rows.append(dict(kind='HMAC',key=key.hex(),message=msg.hex(),actual=actual.hex(),expected=expected.hex(),pass_=actual==expected,run=r))
        print('hmac',len(key),len(msg),r['reason'],actual,actual==expected)
    (OUT/'evidence/digests-original.json').write_text(json.dumps(rows,indent=2))

if __name__=='__main__':
    if len(sys.argv)>1 and sys.argv[1]=='digest':digest_probe()
    else:constants()
