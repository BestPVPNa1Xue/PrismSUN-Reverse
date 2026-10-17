"""Compare the compiled C++ implementation against Python hashlib/hmac.

This is NOT execution of the original ELF. Control-flow expectations come from
the IDA evidence; standard cryptographic outputs have an independent oracle.
"""
import hashlib
import hmac
import json
import os
from pathlib import Path
import random
import subprocess

ROOT=Path(__file__).resolve().parents[1]
EXE=ROOT/'build/host/prism_mcp_clock.exe'
env=dict(os.environ)
env['PATH']='D:/msys64/ucrt64/bin;'+env.get('PATH','')
cases=[]

def run(*args):
    return subprocess.run([str(EXE),*map(str,args)],check=True,capture_output=True,
                          text=True,env=env).stdout.strip()

def verify(name,got,expected,**extra):
    ok=got==expected
    cases.append(dict(name=name,passed=ok,**extra,
                      output_sha256=hashlib.sha256(bytes.fromhex(got)).hexdigest()))
    if not ok: raise AssertionError(name)

def drbg_oracle(algorithm,seed,additional,n):
    size=hashlib.new(algorithm).digest_size
    key=bytes(size)
    value=b'\x01'*size
    def mac(message): return hmac.digest(key,message,algorithm)
    def update(data):
        nonlocal key,value
        key=mac(value+b'\x00'+data)
        value=mac(value)
        if data:
            key=mac(value+b'\x01'+data)
            value=mac(value)
    if not n:
        update(additional)
        return b''
    update(seed)
    result=bytearray()
    while len(result)<n:
        count=min(65536,n-len(result))
        if additional: update(additional)
        chunk=bytearray()
        while len(chunk)<count:
            value=mac(value)
            chunk.extend(value[:count-len(chunk)])
        update(additional)
        additional=b''
        result.extend(chunk)
    return bytes(result)

def main():
    rng=random.Random(0x4D4350434C4F434B)
    for bits in [256,512]:
        name='sha'+str(bits)
        for n in [0,1,3,55,56,63,64,65,111,112,127,128,129,255,1024,4096]:
            msg=rng.randbytes(n)
            verify('hash',run('hash'+str(bits),msg.hex()),hashlib.new(name,msg).hexdigest(),bits=bits,length=n)
        for key_size in [0,1,32,64,65,127,128,129,256]:
            key=rng.randbytes(key_size);msg=rng.randbytes(173)
            verify('hmac',run('hmac'+str(bits),key.hex(),msg.hex()),hmac.digest(key,msg,name).hex(),bits=bits,key_length=key_size)
        for n in [0,1,31,32,63,64,65,128,1000,65536,65537,131073]:
            for add_size in [0,32]:
                seed=rng.randbytes(32);additional=rng.randbytes(add_size)
                verify('drbg',run('drbg',bits,seed.hex(),additional.hex(),n),
                       drbg_oracle(name,seed,additional,n).hex(),bits=bits,length=n,additional_length=add_size)
    report=dict(scope='C++ versus independent hashlib/hmac SHA-2 and DRBG oracle',
                original_elf_executed=False,seed='0x4D4350434C4F434B',
                total=len(cases),passed=sum(c['passed'] for c in cases),cases=cases)
    (ROOT/'evidence/oracle-tests.json').write_text(json.dumps(report,indent=2),encoding='utf-8')
    print(json.dumps({k:report[k] for k in ['total','passed','original_elf_executed']}))

if __name__=='__main__':main()
