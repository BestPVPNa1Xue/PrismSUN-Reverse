import json,struct,re
from pathlib import Path
from direct_fixture import DirectFixture
from unicorn.arm64_const import UC_ARM64_REG_SP

def case(lines,baseline=0,fd=5):
 cursor=0;views={};nexta=0x31100000;state=0x311f0000;records=[];out=0x311e0000
 strings={}
 for row in json.loads((Path(__file__).resolve().parents[1]/'strings.json').read_text()):
  strings[int(row['getter']['function'],16)]=row['text']
 def alloc(f,s):
  nonlocal nexta
  a=nexta;nexta+=4096;f.u.mem_write(a,s.encode()+b'\0');return a
 def cstr(f,a):return bytes(f.u.mem_read(a,4096)).split(b'\0')[0].decode(errors='replace')
 def model(f,c,a):
  nonlocal cursor
  t=c['target'];r=c['resolved']
  if t in strings:return alloc(f,strings[t])
  if t in [0x2b775c,0x2cc4c8,0x2a3c14,0x307e34,0x307e38,0x307ea0,0x307ea8,0x228028,0x271f64]:return a[0]
  if r==0x2d55b0:return state
  if t in [0x307dd0,0x5c5640,0x623750,0x2ddca4,0x5de580,0x307ec4]:return 0
  if t==0xd9d0c:f.u.mem_write(a[0],bytes(24));return a[0]
  if t==0x5da2d8:return 0
  if t==0xc86f4:return a[0]
  if t==0x12d684:return alloc(f,'/proc/self/maps')
  if t==0x2d7e94:return fd
  if t==0x623980:return 0x310d0000
  if t==0x2d96bc:f.u.mem_write(a[0],struct.pack('<Q',a[1]));return a[0]
  if t==0x2d97f8:return 0x310d0000
  if r==0x623990:
   if cursor>=len(lines):return -1
   line=lines[cursor];cursor+=1;p=alloc(f,line);f.u.mem_write(a[0],struct.pack('<Q',p));f.u.mem_write(a[1],struct.pack('<Q',4096));return len(line)
  if t==0x623660:f.u.mem_write(a[0],bytes(a[2]));return a[0]
  if t==0x2da238:return a[0]
  if t==0x6238c0:
   s=cstr(f,a[0]);sp=f.u.reg_read(UC_ARM64_REG_SP);inode,nptr=struct.unpack('<QQ',f.u.mem_read(sp,16))
   m=re.match(r'([0-9a-f]+)-([0-9a-f]+)\s+(\S{1,4})\s+([0-9a-f]+)\s+([0-9a-f]+):([0-9a-f]+)(?:\s+(\d+)\s*)?',s)
   if not m:records.append(dict(parse=s,assigned=0));return 0
   for ptr,val,size in [(a[2],int(m[1],16),8),(a[3],int(m[2],16),8),(a[5],int(m[4],16),8),(a[6],int(m[5],16),4),(a[7],int(m[6],16),4)]:f.u.mem_write(ptr,val.to_bytes(size,'little'))
   f.u.mem_write(a[4],m[3].encode()+b'\0')
   if m[7] is not None:f.u.mem_write(inode,int(m[7]).to_bytes(8,'little'));f.u.mem_write(nptr,m.end().to_bytes(4,'little'))
   records.append(dict(parse=s,assigned=7 if m[7] else 6,n_value=int.from_bytes(f.u.mem_read(nptr,4),'little')));return 7 if m[7] else 6
  if t==0x2da5b0:return int(chr(a[0]).isspace())
  if r==0x2dacb8:return a[0]+a[1]
  if t==0xc8a6c:views[a[0]]=cstr(f,a[1]);return a[0]
  if r==0xc9368:return int(not views[a[0]])
  if t==0x2db100:return views[a[0]].find(cstr(f,a[1]))
  if t==0x160f08:return int(views[a[0]].startswith(cstr(f,a[1])))
  if r==0x12affc:return 1
  if t==0x307e3c:records.append(dict(open_error_object=True));return 0x310c0000
  if t==0x2d83cc:records.append(dict(error_vector_append=True));return 0
  if t==0x307e40:return 0
  raise RuntimeError((hex(c['site']),hex(t),list(map(hex,a))))
 f=DirectFixture(0x2d46ec,model);f.u.mem_write(state+16,struct.pack('<III',baseline,99,77));r=f.run(0x2d46ec,[0]*8+[out]);counts=struct.unpack('<III',f.u.mem_read(state+16,12))
 return dict(lines=lines,baseline=baseline,fd=fd,execution=r,state16_20_24=list(counts),decisions=records,calls=f.calls)
if __name__=='__main__':
 cases=[([],0,5),([],3,5),([],3,-1),(['1000-7000 r-xp 0 00:00 0\n'],0,5),(['1000-6000 r-xp 0 00:00 0\n'],0,5),(['1000-7000 rw-p 0 00:00 0\n'],0,5),(['1000-7000 r-xp 0 00:00 0 /dev/zero (deleted)\n'],0,5),(['1000-7000 r-xp 0 00:00 0 [anon:dalvik]\n'],2,5),(['1000-7000 r-xp 0 00:00 0 /data/app/a.so\n'],0,5),(['1000-7000 r-xp 0 00:00 0 [anon:'],0,5),(['7000-1000 r-xp 0 00:00 0\n'],0,5),(['1000-7000 r-xp 0 00:00 X\n'],0,5)]
 rows=[]
 for lines,b,fd in cases:
  row=case(lines,b,fd);rows.append(row);print(lines,b,fd,row['execution'],row['state16_20_24'],flush=True)
 (Path(__file__).resolve().parents[1]/'maps-fixtures.json').write_text(json.dumps(rows,indent=2))
