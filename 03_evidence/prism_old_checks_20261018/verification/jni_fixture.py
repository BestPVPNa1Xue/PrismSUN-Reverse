"""Run original ARM64 JNI branches against an in-memory JNI model only."""
import json,struct,sys
from pathlib import Path
from bounded_strings import Fixture,STARTS
from unicorn.arm64_const import *

class JNI(Fixture):
 def __init__(self,config=None):
  super().__init__();self.config=config or {};self.log=[];self.objects={};self.serial=0x1000;self.hooks={};self.index=0
  self.decoded={};self.converters=set()
  for fn in ['strings.json']:
   for row in json.loads((Path(__file__).resolve().parents[1]/fn).read_text()):
    if row['text'] is not None:
     self.decoded[int(row['getter']['function'],16)]=row['text'];self.converters.add(int(row['converter']['function'],16))
  self.decoded[0x268ed0]='disableHooks';self.converters.add(0x230498)
  self.env=0x31100000;self.table=0x31101000
  self.u.mem_write(self.env,struct.pack('<Q',self.table))
  self.u.mem_write(self.table,b''.join(struct.pack('<Q',0x33000000+n) for n in range(0,2048,8)))
 def closure(self,root):return set(STARTS)
 def obj(self,v):
  self.serial+=8;self.objects[self.serial]=v;return self.serial
 def alloc(self,s):
  a=self.next;raw=s.encode()+b'\0';self.next+=(len(raw)+255)&~255;self.u.mem_write(a,raw);return a
 def str(self,a):return bytes(self.u.mem_read(a,512)).split(b'\0')[0].decode(errors='replace') if a else ''
 def hook(self,u,a,n,data):
  args=[u.reg_read(UC_ARM64_REG_X0+i) for i in range(9)]
  if a in self.decoded:self.ret(self.alloc(self.decoded[a]));return
  if a in self.converters:self.ret(args[0]);return
  if a in self.hooks:
   r=self.hooks[a](args);self.log.append(dict(helper=hex(a),args=[hex(x) for x in args[:4]],result=r));self.ret(r);return
  if a==0x623640:u.mem_write(args[0],bytes(u.mem_read(args[1],args[2])));self.ret(args[0]);return
  if a==0x623610:self.ret(len(self.str(args[0])));return
  if a==0x623820:self.ret(self.alloc(self.str(args[0])));return
  if a==0x623750:self.ret(0);return
  if a==0x623780:
   b1=bytes(u.mem_read(args[0],args[2]));b2=bytes(u.mem_read(args[1],args[2]));self.ret((b1>b2)-(b1<b2)&0xffffffffffffffff);return
  w=int.from_bytes(u.mem_read(a,4),'little')
  if w&0xfffffc1f==0xd63f0000:
   target=u.reg_read(UC_ARM64_REG_X0+((w>>5)&31));slot=target-0x33000000
   if not 0<=slot<2048:raise RuntimeError(('unexpected BLR',hex(a),hex(target)))
   r=self.jni(slot,args)
   self.log.append(dict(site=hex(a),slot=slot,args=[self.objects.get(x,hex(x)) for x in args[:5]],result=self.objects.get(r,r)))
   u.reg_write(UC_ARM64_REG_X0,r&0xffffffffffffffff);u.reg_write(UC_ARM64_REG_PC,a+4);return
  super().hook(u,a,n,data)
 def jni(self,s,a):
  if s==48:return self.obj(('class',self.str(a[1])))
  if s in [264,904,752,1152]:
   name=self.str(a[2]);sig=self.str(a[3]);self.log.append(dict(lookup=s,name=name,signature=sig))
   if name in self.config.get('missing',[]):return 0
   return self.obj(('member',name,sig))
  if s in [136,184,1360]:return 0
  if s==1824:return self.config.get('exception',0)
  if s==1336:return self.obj(('string',self.str(a[1])))
  if s==912:return self.config.get('loaded',0x5000)
  if s==1240:return 0
  if s==1160:return self.obj(('map',)) if self.config.get('map',True) else 0
  if s==256:return self.config.get('hashmap',1)
  if s==248:return self.obj(('class','fixtureValue'))
  if s in [296,536]:
   mid=a[2] if s==296 else a[3];name=self.objects[mid][1]
   if name=='isEmpty':return int(self.config.get('empty',False)) if s==296 else int(self.config.get('nonvirtual_empty',False))
   if name=='hasNext':return self.index<self.config.get('values',2)
  if s in [272,512]:
   mid=a[2] if s==272 else a[3];name=self.objects[mid][1]
   if name=='values':return self.obj(('collection',))
   if name=='iterator':return self.obj(('iterator',))
   if name=='next':self.index+=1;return self.obj(('callback',self.index))
  if s==1376:return self.obj(('array',a[1]))
  if s==832:return 0
  raise RuntimeError(('unmodeled JNI',s,[self.objects.get(x,hex(x)) for x in a[:5]]))

def run():
 rows=[]
 for fn,configs in [(0x263228,[{}]),(0x25c1bc,[{}, {'missing':['disableHooks']}]),(0x270110,[{}, {'missing':['sHookedMethodCallbacks']}]),(0x26f654,[{}, {'empty':True},{'empty':True,'nonvirtual_empty':True},{'hashmap':0},{'values':0}])]:
  for cfg in configs:
   f=JNI(cfg)
   f.hooks[0x229f44]=lambda a:f.alloc('renamedCallbacks')
   f.hooks[0x2275cc]=lambda a:f.alloc('elements')
   r=f.run(fn,[f.env,0x5000,f.alloc('de/robv/android/xposed/XposedBridge')]);rows.append(dict(root=hex(fn),config=cfg,execution=r,trace=f.log));print(hex(fn),cfg,r,flush=True)
 (Path(__file__).resolve().parents[1]/'jni-fixtures.json').write_text(json.dumps(rows,indent=2))
if __name__=='__main__':run()
