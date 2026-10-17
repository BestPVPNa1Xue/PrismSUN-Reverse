"""Read saved IDA exports; does not load or execute the sample."""
import argparse, json, re
from pathlib import Path
p=argparse.ArgumentParser()
p.add_argument('files',nargs='+')
p.add_argument('--match',default='')
p.add_argument('--context',type=int,default=0)
p.add_argument('--range',nargs=2)
p.add_argument('--code',action='store_true')
a=p.parse_args()
for pattern in a.files:
 for f in Path('.').glob(pattern):
  j=json.loads(f.read_text(encoding='utf-8-sig'))
  j=j.get('structuredContent',j)
  if a.code: lines=j.get('code','').splitlines()
  else:
   raw=j.get('asm',{}).get('lines',[])
   if a.range: raw=[x for x in raw if int(a.range[0],16)<=int(x['addr'],16)<int(a.range[1],16)]
   lines=[x['addr']+' '+x['instruction'] for x in raw]
  if a.match:
   ids=set()
   for i,l in enumerate(lines):
    if re.search(a.match,l,re.I): ids.update(range(max(0,i-a.context),min(len(lines),i+a.context+1)))
   lines=[lines[i] for i in sorted(ids)]
  print(str(f)+'\n'+'\n'.join(lines))
