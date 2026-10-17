"""Event result -> original JSON/crypto -> output record and ring writer."""
import json,struct
from packet_original import PacketFixture
from event_original import EventFixture,OUTPUT
from device_fixture import *
from unicorn.arm64_const import UC_ARM64_REG_X3,UC_ARM64_REG_X4
class Pipeline(EventFixture,PacketFixture):
    def __init__(self):
        super().__init__()
        for address,name in self.imports.items():
            if name=='__vsprintf_chk':self.handlers[address]=self.number_format
    def number_format(self,_):
        dst=self.uc.reg_read(UC_ARM64_REG_X0);limit=self.uc.reg_read(UC_ARM64_REG_X2)
        fmt=self.cstring(self.uc.reg_read(UC_ARM64_REG_X3));ap=self.uc.reg_read(UC_ARM64_REG_X4)
        stack,grtop,vrtop,groff,vroff=struct.unpack('<QQQii',self.uc.mem_read(ap,32))
        assert fmt in (b'%d',b'%.15g',b'%.17g'),fmt
        val=(struct.unpack('<i',self.uc.mem_read(grtop+groff if groff<0 else stack,4))[0] if fmt==b'%d' else struct.unpack('<d',self.uc.mem_read(vrtop+vroff if vroff<0 else stack,8))[0])
        output=(fmt.decode()%val).encode();assert len(output)+1<=limit
        self.uc.mem_write(dst,output+b'\0');self.modeled.add('vsprintf:bounded_cJSON_number');self.return_value(len(output))
    def _hook(self,uc,address,size,user_data):
        if address==0x5bcdd8:
            self.plaintext=self.get_vector(uc.reg_read(UC_ARM64_REG_X0))
        super()._hook(uc,address,size,user_data)
if __name__=='__main__':
    f=Pipeline();event=f.consume();f.nibble=10
    f.put_vector(DATA+568,bytes(range(32)))
    f.uc.mem_write(DATA+616,struct.pack('<H',0x1234));f.uc.mem_write(DATA+624,struct.pack('<Q',7))
    f.uc.mem_write(DATA+0x2800,b'\xcc'*64)
    r=f.call(0x51e9c4,[OUTPUT],DATA+0x2800)
    obs=dict(event=event,convert_run=r,plaintext=getattr(f,'plaintext',b'').decode('utf8','replace'),record_memory=bytes(f.uc.mem_read(DATA+0x2800,64)).hex(),next_sequence=int.from_bytes(f.uc.mem_read(DATA+624,8),'little'),modeled_boundaries=sorted(f.modeled))
    if r['reason']=='returned':
        # optional<Record>: type at +0, libc++ string +8, engaged +32.
        packet=f.get_string(DATA+0x2808);obs['packet_hex']=packet.hex()
        nonce=b'\0\0\x12\x34'+(7).to_bytes(8,'big')
        from cryptography.hazmat.primitives.ciphers.aead import AESGCM
        obs['packet_oracle_pass']=packet==b'\xa2\x12\x34'+nonce+AESGCM(bytes(range(32))).encrypt(nonce,f.plaintext,None)
        # Output ring pointer through original context getter is static 0x7c06ac.
        q=f.call(0x591b70,[0x7c06ac,5,DATA+0x2808]);obs['ring_run']=q
        obs['ring_prefix_hex']=bytes(f.uc.mem_read(0x7c06ac,64)).hex()
        (OUT/'evidence/output-ring.bin').write_bytes(bytes(f.uc.mem_read(0x7c06ac,0x10008)))
    (OUT/'evidence/pipeline-original.json').write_text(json.dumps(obs,indent=2))
    print({k:v for k,v in obs.items() if k not in ('event','convert_run','ring_run')},flush=True)
    print('conversion',r['reason'],'ring',obs.get('ring_run',{}).get('reason'),flush=True)
