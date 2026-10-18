import struct
from bounded_strings import Fixture,owner
from unicorn.arm64_const import *
class DirectFixture(Fixture):
 def __init__(self,root,model):
  super().__init__();self.root=root;self.model=model;self.calls=[];self.fde=owner(root)
 def hook(self,u,a,n,data):
  if self.fde['start']<=a<self.fde['end']:
   w=int.from_bytes(u.mem_read(a,4),'little')
   if w&0xfc000000==0x94000000:
    off=w&0x3ffffff
    if off&0x2000000:off-=0x4000000
    target=a+off*4;resolved=target
    for _ in range(8):
     if not 0<=resolved<0x700000:break
     tw=int.from_bytes(u.mem_read(resolved,4),'little')
     if tw&0xfc000000!=0x14000000:break
     to=tw&0x3ffffff
     if to&0x2000000:to-=0x4000000
     resolved+=to*4
    c=dict(site=a,target=target,resolved=resolved)
    args=[u.reg_read(UC_ARM64_REG_X0+i) for i in range(9)]
    r=self.model(self,c,args)
    if target!=0x6239c0:self.calls.append(dict(site=hex(a),target=hex(target),resolved=hex(resolved),args=list(map(hex,args)),result=r))
    if r is not None:u.reg_write(UC_ARM64_REG_X0,r&0xffffffffffffffff)
    u.reg_write(UC_ARM64_REG_PC,a+4);return
  super().hook(u,a,n,data)
