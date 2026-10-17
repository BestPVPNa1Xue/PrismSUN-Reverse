"""Bounded original ARM64 env-scope ctor/dtor with a synthetic JavaVM table.

Only three JavaVM ABI endpoints are simulated. No imports, syscalls or host
Java runtime are forwarded. This verifies branches; it is not device execution.
"""
import hashlib
import json
import struct
from pathlib import Path
from elftools.elf.elffile import ELFFile
from unicorn import Uc, UcError, UC_ARCH_ARM64, UC_MODE_ARM, UC_HOOK_CODE
from unicorn.arm64_const import *

ROOT = Path('D:/PrismSUN')
OUT = ROOT/'research/accessibility/evidence/jni-env-scope-emulation.json'
VM, TABLE, ENV, SCOPE = 0x30001000,0x30002000,0x30003000,0x30004000
STUB, STOP = 0x31000000,0x32000000
allowed = [(0x305790,0x306df0), (0x3073fc,0x3079bc)]
scenarios = [
    ('null_vm',True,0,0,0,0,[]),
    ('already_attached',False,0,0,ENV,0,['GetEnv']),
    ('detached_attach_success',False,-2,0,ENV,1,['GetEnv','AttachCurrentThread','DetachCurrentThread']),
    ('detached_attach_failed',False,-2,-1,0,0,['GetEnv','AttachCurrentThread']),
    ('unsupported_version',False,-3,0,0,0,['GetEnv']),
    ('other_GetEnv_error',False,-1,0,0,0,['GetEnv']),
]
results=[]
for name,null_vm,get_status,attach_status,expected_env,expected_owned,expected_calls in scenarios:
    u=Uc(UC_ARCH_ARM64,UC_MODE_ARM)
    u.mem_map(0,0x800000)
    with (ROOT/'libprism-sun.so').open('rb') as source:
        for seg in ELFFile(source).iter_segments():
            if seg['p_type']=='PT_LOAD': u.mem_write(seg['p_vaddr'],seg.data())
    for address,size in [(0x20000000,0x200000),(0x30000000,0x10000),(STUB,0x1000),(STOP,0x1000)]:
        u.mem_map(address,size)
    u.mem_write(VM,struct.pack('<Q',TABLE))
    for slot in [4,5,6]: u.mem_write(TABLE+slot*8,struct.pack('<Q',STUB+slot*4))
    u.mem_write(SCOPE,b'\xcc'*24)
    u.reg_write(UC_ARM64_REG_SP,0x20100000)
    u.reg_write(UC_ARM64_REG_TPIDR_EL0,0x30000000)
    u.reg_write(UC_ARM64_REG_CPACR_EL1,3<<20)
    u.reg_write(UC_ARM64_REG_X0,SCOPE)
    u.reg_write(UC_ARM64_REG_X1,0 if null_vm else VM)
    u.reg_write(UC_ARM64_REG_X30,STOP)
    state={'steps':0,'phase':'constructor','stop':'budget','calls':[]}
    def hook(uc,a,n,_):
        state['steps']+=1
        if a==STOP:
            state['stop']='returned'; uc.emu_stop(); return
        if a in [STUB+4*4,STUB+5*4,STUB+6*4]:
            slot=(a-STUB)//4
            args=[uc.reg_read(UC_ARM64_REG_X0+i) for i in range(3)]
            api={4:'AttachCurrentThread',5:'DetachCurrentThread',6:'GetEnv'}[slot]
            state['calls'].append(dict(api=api,phase=state['phase'],args=[hex(x) for x in args]))
            assert args[0]==VM
            if slot==6:
                assert args[1]==SCOPE+8 and args[2]==0x10006
                # Deliberate non-null out value even on failure verifies that
                # the original scope normalizes errors to env=null.
                uc.mem_write(args[1],struct.pack('<Q',ENV))
                uc.reg_write(UC_ARM64_REG_X0,get_status & 0xffffffff)
            elif slot==4:
                assert args[1]==SCOPE+8 and args[2]==0
                uc.mem_write(args[1],struct.pack('<Q',ENV))
                uc.reg_write(UC_ARM64_REG_X0,attach_status & 0xffffffff)
            else:
                uc.reg_write(UC_ARM64_REG_X0,0)
            uc.reg_write(UC_ARM64_REG_PC,uc.reg_read(UC_ARM64_REG_X30))
            return
        if not any(lo<=a<hi for lo,hi in allowed):
            state.update(stop='unexpected_target',address=hex(a)); uc.emu_stop(); return
        word=int.from_bytes(uc.mem_read(a,4),'little')
        if word & 0xffe0001f==0xd4000001:
            state.update(stop='syscall_blocked',address=hex(a)); uc.emu_stop()
    u.hook_add(UC_HOOK_CODE,hook)
    u.emu_start(0x305790,STOP+4,count=200000)
    assert state['stop']=='returned',state
    fields=bytes(u.mem_read(SCOPE,24))
    vm,env=struct.unpack_from('<QQ',fields)
    owned=fields[16]
    assert (vm,env,owned)==(0 if null_vm else VM,expected_env,expected_owned),(name,fields.hex())
    state.update(phase='destructor',stop='budget')
    u.reg_write(UC_ARM64_REG_SP,0x20100000)
    u.reg_write(UC_ARM64_REG_X0,SCOPE)
    u.reg_write(UC_ARM64_REG_X30,STOP)
    u.emu_start(0x3078cc,STOP+4,count=200000)
    assert state['stop']=='returned',state
    assert [x['api'] for x in state['calls']]==expected_calls,state
    results.append(dict(scenario=name,getenv_status=get_status,attach_status=attach_status,
                        fields=dict(vm=hex(vm),env=hex(env),attached_by_scope=owned),
                        steps=state['steps'],calls=state['calls'],status='PASS'))
payload=dict(sample_sha256=hashlib.sha256((ROOT/'libprism-sun.so').read_bytes()).hexdigest(),
             scope='Original ARM64 ctor/dtor with synthetic JavaVM ABI responses; no Android VM/device execution',
             constructor='0x305790',destructor='0x3078cc',instruction_budget_per_phase=200000,
             results=results,status='PASS')
OUT.write_text(json.dumps(payload,indent=2),encoding='utf-8')
print(json.dumps(dict(status='PASS',scenarios=len(results),output=str(OUT))))
