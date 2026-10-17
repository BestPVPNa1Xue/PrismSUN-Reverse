"""Emulate only function prefixes. Stop before calls, returns and syscalls.
No host syscall forwarding and no execution of the Android module by the OS.
"""
from pathlib import Path
import argparse
import json, struct, re, time
from elftools.elf.elffile import ELFFile
from unicorn import Uc, UC_ARCH_ARM64, UC_MODE_ARM, UC_HOOK_CODE, UC_HOOK_MEM_WRITE, UcError
from unicorn.arm64_const import *
from collections import Counter

ROOT=Path(__file__).resolve().parents[1]
parser=argparse.ArgumentParser()
parser.add_argument('--core',action='store_true')
args=parser.parse_args()
prefix='core_' if args.core else ''
meta=json.loads((ROOT/'evidence/elf_inventory.json').read_text())
u=Uc(UC_ARCH_ARM64,UC_MODE_ARM)
u.mem_map(0,0x800000)
with (ROOT.parent/'libprism-sun.so').open('rb') as f:
    e=ELFFile(f)
    for seg in e.iter_segments():
        if seg['p_type']=='PT_LOAD': u.mem_write(seg['p_vaddr'],seg.data())
for r in meta['relocations']:
    if r['r_info_type']==1027:
        u.mem_write(r['r_offset'],struct.pack('<Q',r['r_addend']))
u.mem_map(0x20000000,0x200000)
u.mem_map(0x30000000,0x10000)
u.reg_write(UC_ARM64_REG_CPACR_EL1,3<<20)
code=bytes(u.mem_read(0,0x800000))
base,end=0x79d450,0x7d2400
initial=bytes(u.mem_read(base,end-base))
written=set(); stop_reason=''; step_count=0
def on_code(uc,a,n,user):
    global stop_reason,step_count
    step_count+=1
    if a+4>len(code): stop_reason='outside_image'; uc.emu_stop(); return
    w=struct.unpack_from('<I',code,a)[0]
    if w&0xfc000000==0x94000000 or w&0xfffffc1f==0xd63f0000:
        stop_reason='call'; uc.emu_stop()
    elif w&0xfffffc1f==0xd65f0000:
        stop_reason='return'; uc.emu_stop()
    elif w&0xffe0001f==0xd4000001:
        stop_reason='syscall'; uc.emu_stop()
def on_write(uc,access,a,n,value,user):
    if base<=a<end: written.update(range(a,min(a+n,end)))
u.hook_add(UC_HOOK_CODE,on_code)
u.hook_add(UC_HOOK_MEM_WRITE,on_write)
starts={x['start']:x for x in meta['fdes']}
textsec=next(s for s in meta['sections'] if s['name']=='.text')
lo,hi=textsec['sh_addr'],textsec['sh_addr']+textsec['sh_size']
for a in range(lo,hi-3,4):
    w=struct.unpack_from('<I',code,a)[0]
    if w&0xfc000000==0x94000000:
        off=w&0x3ffffff
        if off&0x2000000: off-=0x4000000
        target=a+4*off
        if lo<=target<hi: starts.setdefault(target,{'start':target,'size':24})
functions=sorted(starts.values(),key=lambda x:x['start'])
if args.core: functions=[f for f in functions if 0x2aacd4<=f['start']<0x5b8000]
(ROOT/'evidence/prefix_candidates.json').write_text(json.dumps(functions),encoding='utf-8')
results=[]; begin=time.monotonic(); stops=Counter()
regs=[UC_ARM64_REG_X0+i for i in range(29)]+[UC_ARM64_REG_X29,UC_ARM64_REG_X30]
for i,fn in enumerate(functions):
    if fn['size']<24: continue
    u.mem_write(base,initial); written.clear(); stop_reason='instruction_budget'; step_count=0
    for reg in regs: u.reg_write(reg,0)
    u.reg_write(UC_ARM64_REG_SP,0x20100000)
    u.reg_write(UC_ARM64_REG_TPIDR_EL0,0x30000000)
    u.reg_write(UC_ARM64_REG_NZCV,0)
    try: u.emu_start(fn['start'],0x800000,count=50000 if args.core else 3000)
    except UcError as ex: stop_reason=str(ex)
    stops[stop_reason]+=1
    if written:
        runs=[]; first=last=None
        for a in sorted(written):
            if first is None: first=last=a
            elif a==last+1: last=a
            else: runs.append((first,last+1)); first=last=a
        runs.append((first,last+1))
        chunks=[]
        for a,b in runs:
            raw=bytes(u.mem_read(a,b-a))
            texts=[{'address':hex(a+m.start()),'text':m.group().decode('ascii')} for m in re.finditer(rb'[\x20-\x7e]{4,}',raw)]
            if texts or len(raw)>4: chunks.append({'address':hex(a),'bytes':raw.hex(),'strings':texts})
        if chunks: results.append({'function':hex(fn['start']),'stop':stop_reason,'steps':step_count,'chunks':chunks})
    if i%500==0:
        (ROOT/('evidence/'+prefix+'prefix_decode.partial.json')).write_text(json.dumps(results,ensure_ascii=False,indent=2),encoding='utf-8')
        print(f'{i}/{len(functions)} functions, {len(results)} writers, {time.monotonic()-begin:.1f}s',flush=True)
(ROOT/('evidence/'+prefix+'prefix_decode.json')).write_text(json.dumps(results,ensure_ascii=False,indent=2),encoding='utf-8')
rows=[{'function':r['function'],**s} for r in results for c in r['chunks'] for s in c['strings']]
(ROOT/('evidence/'+prefix+'decoded_strings.json')).write_text(json.dumps(rows,ensure_ascii=False,indent=2),encoding='utf-8')
print(f'DONE {len(results)} writers; {len(rows)} strings; {time.monotonic()-begin:.1f}s',flush=True)
(ROOT/('evidence/'+prefix+'prefix_decode_summary.json')).write_text(json.dumps(dict(stops),indent=2),encoding='utf-8')
print(dict(stops),flush=True)
