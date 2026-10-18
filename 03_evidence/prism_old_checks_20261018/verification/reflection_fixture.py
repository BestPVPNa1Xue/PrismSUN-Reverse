import json
from pathlib import Path
from jni_fixture import JNI

class Reflection(JNI):
 def jni(self,s,a):
  obj=self.objects.get(a[1]);member=self.objects.get(a[2],['',''])[1]
  if s==1368:return len(obj[1])
  if s==1384:return obj[1][a[2]]
  if s==192:return int(self.objects.get(a[1])==self.objects.get(a[2]))
  if s==1352:return self.alloc(obj[1])
  if s==392:return obj[1]['flags']
  if s==272:
   if member in ['getDeclaredFields','getDeclaredMethods']:
    kind='field' if member=='getDeclaredFields' else 'method'
    return self.obj(('list',[self.obj((kind,x)) for x in self.config.get('members',[])]))
   if member=='getModifiers':return obj[1]['flags']
   if member in ['getType','getReturnType']:return self.obj(('class',obj[1]['type']))
   if member=='getName':return self.obj(('string',obj[1]['name'] if obj[0] in ['field','method'] else obj[1]))
   if member=='getParameterTypes':return self.obj(('list',[self.obj(('class',t)) for t in obj[1].get('params',[])]))
   if member=='getStackTrace':return self.obj(('list',[self.obj(('frame',n)) for n in self.config.get('stack',[])]))
   if member=='getClassName':return self.obj(('string',obj[1]))
  if s==912:
   if member=='currentThread':return self.obj(('thread',))
   if member=='findLoadedClass':return self.config.get('loaded',0x5000)
   return self.obj(('string',self.config.get('descriptor','Lexample.CallbackOwner;')))
  return super().jni(s,a)

if __name__=='__main__':
 cases=[(0x2275cc,dict(members=[dict(name='staticWrong',flags=8,type='[Ljava/lang/Object;'),dict(name='objects',flags=0,type='[Ljava/lang/Object;')])),
 (0x229f44,dict(members=[dict(name='hash',flags=8,type='java/util/HashMap'),dict(name='callbacks',flags=8,type='java/util/Map')])),
 (0x22b0d4,dict(members=[dict(name='native',flags=0x108,type='java/lang/String'),dict(name='owner',flags=8,type='java/lang/String')],descriptor='Lexample.CallbackOwner;')),
 (0x25dc1c,dict(stack=['normal.Frame','de.robv.android.xposed.XC_MethodHookExtra']))]
 rows=[]
 for item in cases:
  root,cfg=item[:2];f=Reflection(cfg)
  # This signature getter was separately executed from original instructions.
  f.decoded[0x234dfc]='()Ljava/lang/String;';f.converters.add(0x24db80)
  r=f.run(root,[f.env,f.obj(('class','fixture'))]);v=int(r['result'],16)
  text=f.str(v) if r['reason']=='return' and 0x31000000<=v<0x31200000 else None
  row=dict(root=hex(root),config=cfg,execution=r,text=text,global_state=int.from_bytes(f.u.mem_read(0x654a08,4),'little'),trace=f.log);rows.append(row);print(hex(root),r,text,row['global_state'],flush=True)
 (Path(__file__).resolve().parents[1]/'reflection-fixtures.json').write_text(json.dumps(rows,indent=2))

