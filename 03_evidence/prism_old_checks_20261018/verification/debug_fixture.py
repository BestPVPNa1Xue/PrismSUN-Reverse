import json,struct,re
from pathlib import Path
from direct_fixture import DirectFixture
from unicorn.arm64_const import UC_ARM64_REG_X1

def case(content,fd=5):
 pos=0;strings={};allocs={};nexta=0x31100000;decisions=[]
 def alloc(f,s):
  nonlocal nexta
  a=nexta;nexta+=1024;f.u.mem_write(a,s.encode()+b'\0');return a
 def cstr(f,a):return bytes(f.u.mem_read(a,2048)).split(b'\0')[0].decode(errors='replace')
 def model(f,c,a):
  nonlocal pos
  t=c['target'];r=c['resolved']
  getters={0x334ee4:'/status',0x314db4:'r',0x334f4c:'TracerPid:',0x315b14:'State:',0x334f50:'t',0x334f54:'(tracing stop)'}
  if t in getters:return alloc(f,getters[t])
  if t in [0x2339ac,0x269a3c,0x2cc4c8,0x271f64,0x29280c]:return a[0]
  if t in [0x334ee8,0x5de580,0x334f64,0x623880]:return 0
  if t==0x5da2d8:strings[a[8]]='/proc/self';return 0
  if t==0xc86f4:strings[a[0]]=strings.get(a[1],'/proc/self')+cstr(f,a[2]);return a[0]
  if t==0x12d684:return alloc(f,strings.get(a[0],'/proc/self/status'))
  if t==0x314994:return fd
  if t==0x3ee9fc:decisions.append({'abnormal':a[0]});f.reason='abnormal_handler';f.u.emu_stop();return 0
  if r==0x623980:return 0x310c0000
  if t==0x6239c0:
   if pos>=len(content):return -1
   v=ord(content[pos]);pos+=1;return v
  if t==0xc8a6c:
   s=cstr(f,a[1]);strings[a[0]]=s;f.u.mem_write(a[0],struct.pack('<QQ',a[1],len(s)));return a[0]
  if t==0x317a40:
   needle=cstr(f,a[1]);s=strings[a[0]];v=s.find(needle);decisions.append(dict(find=needle,line=s,result=v));return v
  if r==0xcae18:
   s=strings[a[0]][a[1]:];p=alloc(f,s);f.u.reg_write(UC_ARM64_REG_X1,len(s));decisions.append(dict(substr_start=a[1],value=s));return p
  if r==0xca4a4:
   p,n=struct.unpack('<QQ',f.u.mem_read(a[1],16));strings[a[0]]=bytes(f.u.mem_read(p,n)).decode();return a[0]
  if t==0x5df824:
   s=strings[a[0]];m=re.match(r'\s*([+-]?\d+)',s)
   if not m:f.reason='modeled_stoi_invalid_argument';f.u.emu_stop();return 0
   v=int(m[1]);decisions.append(dict(stoi=s,value=v));return v
  if t==0xcc4d0:
   v=strings[a[0]]==cstr(f,a[1]);decisions.append(dict(equal=[strings[a[0]],cstr(f,a[1])],value=v));return int(v)
  raise RuntimeError((hex(c['site']),hex(t),list(map(hex,a))))
 f=DirectFixture(0x3135e0,model);r=f.run(0x3135e0)
 return dict(content=content,fd=fd,execution=r,consumed=pos,decisions=decisions,calls=f.calls)
if __name__=='__main__':
 rows=[]
 for content,fd in [('TracerPid:\t0\n',5),('TracerPid:\t123\n',5),('State:\tt (tracing stop)\nTracerPid:\t9\n',5),('State:\tt\nTracerPid:\t9\n',5),('State:\tt',5),('State:\t(tracing stop)',5),('State:\tS (sleeping)\n',5),('',5),('',0),('',-1),('xxTracerPid:\t9\n',5),('TracerPid:\tbad\n',5)]:
  row=case(content,fd);rows.append(row);print(repr(content),fd,row['execution'],row['decisions'],flush=True)
 (Path(__file__).resolve().parents[1]/'debug-fixtures.json').write_text(json.dumps(rows,indent=2))
