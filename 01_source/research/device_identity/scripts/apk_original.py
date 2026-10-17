"""Original APK-v2 nested field extraction over a synthetic seekable byte stream."""
import hashlib,json,struct
from device_fixture import *
def lp(x):return struct.pack('<I',len(x))+x
def make_apk(cert,comment=b''):
    signed_data=lp(b'DIGEST_RECORDS')+lp(lp(cert)+lp(b'SECOND_CERT'))+lp(b'')
    signer=lp(signed_data)+lp(b'SIGNATURE_RECORDS')+lp(b'PUBLIC_KEY')
    value=lp(lp(signer))
    pair=struct.pack('<QI',len(value)+4,0x7109871a)+value
    size=len(pair)+24
    block=struct.pack('<Q',size)+pair+struct.pack('<Q',size)+b'APK Sig Block 42'
    cd_offset=32+len(block);cd=b'CENTRAL_DIRECTORY'
    eocd=struct.pack('<IHHHHIIH',0x06054b50,0,0,1,1,len(cd),cd_offset,len(comment))+comment
    return b'Z'*32+block+cd+eocd
class APKFixture(DeviceFixture):
    def __init__(self):
        super().__init__();self.handlers[0x4c0d54]=self.seek;self.handlers[0x4c0f3c]=self.read
    def seek(self,_):
        off=self.uc.reg_read(UC_ARM64_REG_X1);off=off-(1<<64) if off>>63 else off
        whence=self.uc.reg_read(UC_ARM64_REG_X2)
        self.pos=(0 if whence==0 else self.pos if whence==1 else len(self.blob))+off
        self.trace.append(dict(api='seek',offset=off,whence=whence,result=self.pos));self.return_value(self.pos)
    def read(self,_):
        p=self.uc.reg_read(UC_ARM64_REG_X1);n=self.uc.reg_read(UC_ARM64_REG_X2)
        assert 0<=self.pos<=len(self.blob) and n<65536
        v=self.blob[self.pos:self.pos+n];self.trace.append(dict(api='read',offset=self.pos,count=n,hex=v.hex()))
        self.uc.mem_write(p,v);self.pos+=len(v);self.return_value(len(v))
    def probe(self,cert,comment=b''):
        self.reset();self.blob=make_apk(cert,comment);self.pos=0;self.trace=[]
        r=self.call(0x4c0718,[17],DATA+0x1000)
        v=self.get_string(DATA+0x1000) if r['reason']=='returned' else b''
        q=self.call(0x3780ec,[DATA+0x1000],DATA+0x1100) if r['reason']=='returned' else {}
        h=self.get_string(DATA+0x1100).decode() if q.get('reason')=='returned' else None
        return dict(certificate_hex=cert.hex(),comment_hex=comment.hex(),extracted_hex=v.hex(),digest=h,pass_=v==cert and h==hashlib.sha256(cert).hexdigest().upper(),extract_run=r,digest_run=q,trace=self.trace,modeled_boundaries=sorted(self.modeled|{'lseek/read_wrappers:synthetic_APK'}))
if __name__=='__main__':
    f=APKFixture();rows=[]
    for cert,comment in [(b'TEST_CERTIFICATE_DER',b''),(bytes(range(65)),b'test zip comment')]:
        r=f.probe(cert,comment);rows.append(r);print(r['extracted_hex'],r['digest'],r['pass_'],r['extract_run']['reason'],r['digest_run'].get('reason'),flush=True)
        (OUT/'evidence/apk-original.json').write_text(json.dumps(rows,indent=2))
        if not r['pass_']:break
