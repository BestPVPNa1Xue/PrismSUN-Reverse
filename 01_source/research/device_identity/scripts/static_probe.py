"""Source-bound ELF/FDE instruction capture; never executes target OS code."""
import argparse, bisect, json, struct
from pathlib import Path
from capstone import Cs, CS_ARCH_ARM64, CS_MODE_ARM
from elftools.elf.elffile import ELFFile

ROOT = Path(__file__).resolve().parents[3]
OUT = ROOT / 'research/device_identity'
meta = json.loads((ROOT/'research/evidence/elf_inventory.json').read_text())
image = bytearray(0x800000)
with (ROOT/'libprism-sun.so').open('rb') as f:
    for s in ELFFile(f).iter_segments():
        if s['p_type'] == 'PT_LOAD':
            image[s['p_vaddr']:s['p_vaddr']+s['p_filesz']] = s.data()
fdes = sorted(meta['fdes'], key=lambda x:x['start'])
starts = [x['start'] for x in fdes]
md = Cs(CS_ARCH_ARM64, CS_MODE_ARM); md.skipdata = True
def boundary(a):
    i = bisect.bisect_right(starts,a)-1
    f = fdes[i] if i >= 0 else {}
    return f if f.get('start',a+1)<=a<f.get('end',0) else None
def capture(a, size=None):
    f = boundary(a)
    lo,hi = (a,a+size) if size else ((f['start'],f['end']) if f else (a,a+0x80))
    ins = list(md.disasm(bytes(image[lo:hi]),lo))
    row = dict(start=hex(lo),end=hex(hi),fde=f,
               asm='\n'.join(f'{i.address:#x}: {i.mnemonic} {i.op_str}' for i in ins))
    (OUT/f'evidence/asm-{hex(lo)}.json').write_text(json.dumps(row,indent=2))
    (OUT/f'evidence/asm-{hex(lo)}.txt').write_text(row['asm'])
    return row
if __name__ == '__main__':
    p = argparse.ArgumentParser(); p.add_argument('addresses',nargs='*'); p.add_argument('--size',type=lambda s:int(s,0)); p.add_argument('--strings',action='store_true'); p.add_argument('--print',action='store_true',dest='show')
    a = p.parse_args()
    for v in a.addresses:
        r=capture(int(v,0),a.size); print(json.dumps(r if a.show else {k:v for k,v in r.items() if k!='asm'}))
    if a.strings:
        rows=json.loads((ROOT/'research/evidence/stage2_strings.json').read_text())
        terms=('device','finger','android_id','serial','drm','uuid','imei','license','boot','machine','mac','media','version','brand','model','aid','widevine','network','http')
        matches=[r for r in rows if any(s in r['plaintext'].lower() for s in terms)]
        (OUT/'evidence/string-leads.json').write_text(json.dumps(matches,indent=2))
        for r in matches:print(r['writer'],r['plaintext'],r['caller_evidence'])
