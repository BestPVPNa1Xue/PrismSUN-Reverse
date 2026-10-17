"""Original AES-GCM framing, with fixed nibble and inert libc; independent oracle."""
import json,struct
from cryptography.hazmat.primitives.ciphers.aead import AESGCM
from device_fixture import *
class PacketFixture(DeviceFixture):
    def __init__(self):
        super().__init__()
        self.handlers[0x5b8280]=self.random_nibble
        for address,name in self.imports.items():
            if name in ('newlocale','uselocale'):
                self.handlers[address]=lambda f,n=name:f.locale(n)
            elif name=='freelocale':self.handlers[address]=lambda f:f.return_value(0)
    def locale(self,name):
        self.modeled.add(name+':synthetic_C_locale');self.return_value(DATA+0x1800)
    def random_nibble(self,_):
        assert self.uc.reg_read(UC_ARM64_REG_X0)==0 and self.uc.reg_read(UC_ARM64_REG_X1)==15
        self.modeled.add('random_nibble:fixed_test_value');self.return_value(self.nibble)
    def encrypt(self,msg,key=bytes(range(32)),generation=0x1234,sequence=0x0102030405060708,nibble=10):
        self.reset();self.nibble=nibble
        self.put_vector(DATA,msg);self.put_vector(DATA+0x100,key)
        r=self.call(0x5bcdd8,[DATA,DATA+0x100,generation,sequence],DATA+0x200)
        actual=self.get_vector(DATA+0x200) if r['reason']=='returned' else b''
        nonce=b'\0\0'+generation.to_bytes(2,'big')+sequence.to_bytes(8,'big')
        expected=bytes([nibble<<4|2])+generation.to_bytes(2,'big')+nonce+AESGCM(key).encrypt(nonce,msg,None)
        return dict(plaintext_hex=msg.hex(),key_hex=key.hex(),generation=generation,sequence=sequence,nibble=nibble,nonce_hex=nonce.hex(),actual_hex=actual.hex(),expected_hex=expected.hex(),pass_=actual==expected,run=r,modeled_boundaries=sorted(self.modeled))
if __name__=='__main__':
    f=PacketFixture();rows=[]
    for msg,nibble in [(b'',0),(b'abc',10),(bytes(range(65)),15)]:
        r=f.encrypt(msg,nibble=nibble);rows.append(r);print(r,flush=True)
        (OUT/'evidence/packet-original.json').write_text(json.dumps(rows,indent=2))
        if r['run']['reason']!='returned':break
