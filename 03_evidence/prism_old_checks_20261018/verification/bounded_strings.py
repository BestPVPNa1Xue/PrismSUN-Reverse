"""Execute only string-getter call graphs in Unicorn; model TLS/destructor registration.
No syscalls, no process/Android execution, no external imports forwarded.
"""
from pathlib import Path
import json,struct,bisect
from elftools.elf.elffile import ELFFile
from unicorn import *
from unicorn.arm64_const import *
ROOT=Path(__file__).resolve().parents[1]
import os
SAMPLE=Path(os.environ['PRISM_OLD_SAMPLE'])
FDE=json.loads((ROOT/'fixture-ranges.json').read_text())
STARTS=[x['start'] for x in FDE]
CALLS=[]
def owner(a):
 i=bisect.bisect_right(STARTS,a)-1
 return FDE[i] if i>=0 and a<FDE[i]['end'] else None
class Fixture:
 def __init__(self):
  self.u=u=Uc(UC_ARCH_ARM64,UC_MODE_ARM);u.mem_map(0,0x700000)
  with SAMPLE.open('rb') as f:
   e=ELFFile(f)
   for s in e.iter_segments():
    if s['p_type']=='PT_LOAD':u.mem_write(s['p_vaddr'],s.data())
   for s in e.iter_sections():
    if s['sh_type']=='SHT_RELA':
     for r in s.iter_relocations():
      if r['r_info_type']==1027:u.mem_write(r['r_offset'],struct.pack('<Q',r['r_addend']))
  for a,n in [(0x20000000,0x200000),(0x30000000,0x10000),(0x31000000,0x200000),(0x32000000,0x1000)]:u.mem_map(a,n)
  u.reg_write(UC_ARM64_REG_CPACR_EL1,3<<20);self.tls={};self.next=0x31000000;self.events=[];self.reason='';self.seen=set();self.allow=set();self.steps=0
  u.hook_add(UC_HOOK_CODE,self.hook)
 def ret(self,v=None):
  if v is not None:self.u.reg_write(UC_ARM64_REG_X0,v)
  self.u.reg_write(UC_ARM64_REG_PC,self.u.reg_read(UC_ARM64_REG_X30))
 def hook(self,u,a,n,_):
  self.steps+=1
  if a==0x32000000:self.reason='return';u.emu_stop();return
  args=[u.reg_read(UC_ARM64_REG_X0+i) for i in range(3)]
  if a==0x61e95c:
   desc=args[0]
   if desc not in self.tls:
    size,align,index,init=struct.unpack('<QQQQ',u.mem_read(desc,32));assert size<0x10000
    self.tls[desc]=self.next;self.next+=(size+255)&~255
    u.mem_write(self.tls[desc],bytes(u.mem_read(init,size)) if init else bytes(size))
   self.events.append(dict(boundary='emutls_get_address',descriptor=hex(desc),result=hex(self.tls[desc])))
   self.ret(self.tls[desc]);return
  if a==0x61e0bc:self.events.append(dict(boundary='thread_atexit',args=list(map(hex,args))));self.ret(0);return
  if a==0x623650:
   assert args[2]<0x10000;u.mem_write(args[0],bytes(u.mem_read(args[1],args[2])));self.ret(args[0]);return
  if a==0x623660:
   assert args[2]<0x10000;u.mem_write(args[0],bytes([args[1]&255])*args[2]);self.ret(args[0]);return
  if not 0xbdc60<=a<0x6235b0:self.reason='blocked_outside_text_'+hex(a);u.emu_stop();return
  f=owner(a)
  if f:
   if f['start'] not in self.allow:self.reason='blocked_nonallowlisted_'+hex(a);u.emu_stop();return
   self.seen.add(f['start'])
  w=struct.unpack('<I',u.mem_read(a,4))[0]
  if w&0xffe0001f==0xd4000001:self.reason='blocked_syscall';u.emu_stop()
  if w&0xfffffc1f==0xd63f0000:self.reason='blocked_indirect_call';u.emu_stop()
 def closure(self,root):return set(STARTS)
 def run(self,fn,args=()):
  u=self.u;self.allow=self.closure(fn);self.reason='budget';self.steps=0
  for i in range(29):u.reg_write(UC_ARM64_REG_X0+i,0)
  u.reg_write(UC_ARM64_REG_X29,0);u.reg_write(UC_ARM64_REG_X30,0x32000000);u.reg_write(UC_ARM64_REG_SP,0x20100000);u.reg_write(UC_ARM64_REG_TPIDR_EL0,0x30000000);u.reg_write(UC_ARM64_REG_NZCV,0)
  for i,v in enumerate(args):u.reg_write(UC_ARM64_REG_X0+i,v)
  try:u.emu_start(fn,0x32000004,count=1500000,timeout=15000000)
  except UcError as ex:self.reason=str(ex)
  return dict(function=hex(fn),reason=self.reason,steps=self.steps,pc=hex(u.reg_read(UC_ARM64_REG_PC)),result=hex(u.reg_read(UC_ARM64_REG_X0)))
