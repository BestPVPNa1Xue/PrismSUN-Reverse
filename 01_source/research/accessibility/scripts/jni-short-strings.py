"""Recover the two four-byte JNI tokens omitted by the older >4-byte filter."""
import hashlib
import json
import struct
from pathlib import Path
from elftools.elf.elffile import ELFFile
from unicorn import Uc, UC_ARCH_ARM64, UC_MODE_ARM, UC_HOOK_CODE, UcError
from unicorn.arm64_const import *

ROOT = Path('D:/PrismSUN')
meta = json.loads((ROOT/'research/evidence/elf_inventory.json').read_text())
params = json.loads((ROOT/'research/evidence/stage2_keys.json').read_text())
results = []
for writer, data, wrapper in [(0x329e7c,0x7ac990,0x32a808), (0x32ce7c,0x7ac9f0,0x32d77c)]:
    u = Uc(UC_ARCH_ARM64, UC_MODE_ARM)
    u.mem_map(0,0x800000)
    with (ROOT/'libprism-sun.so').open('rb') as source:
        for seg in ELFFile(source).iter_segments():
            if seg['p_type']=='PT_LOAD': u.mem_write(seg['p_vaddr'],seg.data())
    for r in meta['relocations']:
        if r['r_info_type']==1027: u.mem_write(r['r_offset'],struct.pack('<Q',r['r_addend']))
    u.mem_map(0x20000000,0x200000)
    u.mem_map(0x30000000,0x10000)
    u.reg_write(UC_ARM64_REG_CPACR_EL1,3<<20)
    u.reg_write(UC_ARM64_REG_SP,0x20100000)
    u.reg_write(UC_ARM64_REG_TPIDR_EL0,0x30000000)
    state={'steps':0,'stop':'instruction_budget'}
    def hook(uc,a,n,_):
        state['steps']+=1
        if not 0<=a<0x800000:
            state.update(stop='outside_image',address=hex(a)); uc.emu_stop(); return
        w=int.from_bytes(uc.mem_read(a,4),'little')
        if w&0xfc000000==0x94000000 or w&0xfffffc1f==0xd63f0000:
            state.update(stop='before_call',address=hex(a)); uc.emu_stop()
        elif w&0xfffffc1f==0xd65f0000 or w&0xffe0001f==0xd4000001:
            state.update(stop='before_return_or_syscall',address=hex(a)); uc.emu_stop()
    u.hook_add(UC_HOOK_CODE,hook)
    try: u.emu_start(writer,0x800000,count=50000)
    except UcError as e: state['stop']=str(e)
    row=next(x for x in params if int(x['wrapper'],0)==wrapper)
    encrypted=bytes(u.mem_read(data,4)); key=int(row['key'],0).to_bytes(8,'little')
    decoded=bytes(a^b for a,b in zip(encrypted,key))
    results.append(dict(writer=hex(writer),data=hex(data),wrapper=hex(wrapper),length=4,
                        encrypted=encrypted.hex(),decoder_parameters=row,
                        plaintext=decoded.rstrip(b'\0').decode(),bytes=decoded.hex(),prefix=state))
assert [x['plaintext'] for x in results]==['get','()I']
payload=dict(sample_sha256=hashlib.sha256((ROOT/'libprism-sun.so').read_bytes()).hexdigest(),
             method='bounded writer prefixes stop before every call; XOR parameters from prior bounded wrapper capture',
             no_host_calls=True,results=results)
path=ROOT/'research/accessibility/evidence/jni-short-strings.json'
path.write_text(json.dumps(payload,indent=2),encoding='utf-8')
print(json.dumps(payload,indent=2))
