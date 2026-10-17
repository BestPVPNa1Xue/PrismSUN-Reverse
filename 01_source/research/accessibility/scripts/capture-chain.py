import sys, json, urllib.request, bisect
from pathlib import Path
from capstone import Cs,CS_ARCH_ARM64,CS_MODE_ARM
from elftools.elf.elffile import ELFFile
ROOT=Path(__file__).resolve().parents[3]
OUT=ROOT/'research/accessibility'
meta=json.loads((ROOT/'research/evidence/elf_inventory.json').read_text())
image=bytearray(0x800000)
with (ROOT/'libprism-sun.so').open('rb') as f:
 for s in ELFFile(f).iter_segments():
  if s['p_type']=='PT_LOAD': image[s['p_vaddr']:s['p_vaddr']+s['p_filesz']]=s.data()
fdes=sorted(meta['fdes'],key=lambda f:f['start']); starts=[f['start'] for f in fdes]
md=Cs(CS_ARCH_ARM64,CS_MODE_ARM);md.skipdata=True
raw=json.loads((OUT/'evidence/consumer-raw.json').read_text()) if (OUT/'evidence/consumer-raw.json').exists() else {}
def capture(a):
 f=fdes[bisect.bisect_right(starts,a)-1]
 lo,hi=(f['start'],f['end']) if f['start']<=a<f['end'] else (a,a+0x90)
 if hex(lo) in raw:return
 ins=list(md.disasm(bytes(image[lo:hi]),lo))
 raw[hex(lo)]={'end':hex(hi),'fde':f if f['start']<=a<f['end'] else None,'asm':'\n'.join(f'{i.address:#x}: {i.mnemonic} {i.op_str}' for i in ins)}
 if hi-lo==4 and ins[0].mnemonic=='b': capture(int(ins[0].op_str.lstrip('#'),0))
for s in sys.argv[1:]:capture(int(s,0))
(OUT/'evidence/consumer-raw.json').write_text(json.dumps(raw,indent=2))
for s in sys.argv[1:]:
 body={'jsonrpc':'2.0','id':1,'method':'tools/call','params':{'name':'decompile','arguments':{'addr':s}}}
 req=urllib.request.Request('http://127.0.0.1:47083/mcp',json.dumps(body).encode(),headers={'Content-Type':'application/json'})
 with urllib.request.urlopen(req,timeout=120) as r:result=json.load(r)
 (OUT/f'decompiled/{s}.json').write_text(json.dumps(result,indent=2))
 result=result.get('result',{}); data=result.get('structuredContent')
 if data is None:data=json.loads(result.get('content',[{'text':'{}'}])[0]['text'])
 code=data.get('code')
 if code:(OUT/f'decompiled/{s}.c').write_text(code)
 print(s,len(code or ''),data.get('error',''))
