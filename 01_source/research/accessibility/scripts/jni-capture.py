"""Read-only raw ELF capture of accessibility JNI wrappers and immediate thunks."""
import bisect
import hashlib
import json
from pathlib import Path

from capstone import Cs, CS_ARCH_ARM64, CS_MODE_ARM
from elftools.elf.elffile import ELFFile

ROOT = Path('D:/PrismSUN')
OUT = ROOT / 'research/accessibility/evidence'
sample = ROOT / 'libprism-sun.so'
meta = json.loads((ROOT / 'research/evidence/elf_inventory.json').read_text())
image = bytearray(0x800000)
with sample.open('rb') as source:
    elf = ELFFile(source)
    for segment in elf.iter_segments():
        if segment['p_type'] == 'PT_LOAD':
            image[segment['p_vaddr']:segment['p_vaddr'] + segment['p_filesz']] = segment.data()
fdes = sorted(meta['fdes'], key=lambda x: x['start'])
starts = [f['start'] for f in fdes]
decoder = Cs(CS_ARCH_ARM64, CS_MODE_ARM)
decoder.skipdata = True
seeds = [0x31b73c, 0x2db974, 0x2dce08, 0x2dd338, 0x2e05e0, 0x320984,
         0x320d04, 0x2e3e98, 0x2e4448, 0x332358, 0x331f98, 0x2e5024,
         0x2e8d48, 0x2e4ef4, 0x2e4dd0, 0x2e1048, 0x2e49dc, 0x13f5e4]
seeds += list(range(0x34aab4, 0x34ab70, 4))
seeds += [0x2e00cc, 0x2e0a2c, 0x301194, 0x3054a4, 0x3054a8,
          0x3054ac, 0x2e579c, 0x30543c, 0x305444, 0x305448]
seeds += [0x329e7c, 0x32a808, 0x32ce7c, 0x32d77c]
seeds += [0x306df0, 0x308130, 0x3071a8, 0x305790, 0x306404,
          0x306930, 0x3073fc, 0x3078cc, 0x3079bc, 0x307d30]
result = {}
def capture(address):
    f = fdes[bisect.bisect_right(starts, address) - 1]
    if not f['start'] <= address < f['end']:
        return
    start, end = f['start'], f['end']
    if hex(start) in result:
        return
    insns = [dict(address=hex(i.address), bytes=i.bytes.hex(), mnemonic=i.mnemonic, op_str=i.op_str)
             for i in decoder.disasm(bytes(image[start:end]), start)]
    result[hex(start)] = dict(start=hex(start), end=hex(end), instructions=insns)
    if end-start == 4 and insns and insns[0]['mnemonic'] == 'b':
        capture(int(insns[0]['op_str'].lstrip('#'), 0))
for a in seeds:
    capture(a)
payload = dict(sample=str(sample), sha256=hashlib.sha256(sample.read_bytes()).hexdigest(),
               source='PT_LOAD bytes mapped at p_vaddr; .eh_frame FDE boundaries', functions=result)
(OUT / 'jni-raw-wrappers.json').write_text(json.dumps(payload, indent=2), encoding='utf-8')
text = '\n\n'.join(f'{k} - {v["end"]}\n' + '\n'.join(f'{i["address"]}: {i["mnemonic"]} {i["op_str"]}' for i in v['instructions']) for k,v in result.items())
(OUT / 'jni-raw-wrappers.txt').write_text(text, encoding='utf-8')
print(json.dumps(dict(functions=len(result), output=str(OUT / 'jni-raw-wrappers.json'))))
