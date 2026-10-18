import json
from pathlib import Path
from direct_fixture import DirectFixture
from jni_fixture import JNI

root=Path(__file__).resolve().parents[1]
for expected in [0,-1]:
 def model(f,c,args):
  assert c['target']==0x312748
  assert args[0]&0xffffffff==0xffffff9c and args[3]==0
  return expected
 f=DirectFixture(0x30f590,model)
 result=f.run(0x30f590,[0x31100000,0x31100100])
 assert result['reason']=='return' and int(result['result'],16)&0xffffffff==expected&0xffffffff
f=JNI();a=f.run(0x2d8a4c);assert a['reason']=='return'
b=f.run(0x2dea08,[0x31130000,int(a['result'],16)]);assert b['reason']=='return'
obj=bytes(f.u.mem_read(0x31130000,24));assert obj[:4]==b'\x048)\0'
print('PASS: fstatat wrapper arguments, both return paths, and original diagnostic 8)')
