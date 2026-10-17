"""Verify saved evidence/delivery identities; does not execute the original SO."""
import hashlib
import json
import re
from datetime import datetime, timezone, timedelta
from pathlib import Path
import zipfile

ROOT=Path(__file__).resolve().parents[1]
def sha(path):return hashlib.sha256(path.read_bytes()).hexdigest()
def read(name):return json.loads((ROOT/name).read_text(encoding='utf-8-sig'))

before=read('evidence/protected-before.json')
after=[]
for item in before:
    path=Path(item['Path'])
    current=sha(path)
    assert current.lower()==item['Hash'].lower(),f'protected file changed: {path}'
    after.append(dict(Path=str(path),Hash=current))
(ROOT/'evidence/protected-after.json').write_text(json.dumps(after,indent=2),encoding='utf-8')

def raw(name,index=0):
    return bytes(int(x,16) for x in read(name)['result'][index]['data'].split())
base=raw('evidence/focus-4.json')
proc=raw('evidence/follow-3.json',3)
def xor(*items):return bytes(a^b for a,b in zip(items[0],items[1]))
assert xor(xor(base[20:24],bytes.fromhex('5be30375')),bytes.fromhex('e3fba15f'))==b'/fd\0'
assert xor(xor(base[120:124],bytes.fromhex('ab097bda')),bytes.fromhex('e35dfd0f'))==b'/fd\0'
assert xor(xor(proc[:7],bytes.fromhex('d2982065a04cd8')),bytes.fromhex('4589c7d3734969'))==b'/proc/\0'
assert xor(xor(base[48:52],bytes.fromhex('f1694c2a')),b'\x07'*4)==b'MCPK'
assert xor(base[4:6],bytes.fromhex('5377'))==b':\0'

unit=(ROOT/'evidence/unit-tests.txt').read_text(encoding='utf-8-sig').strip()
assert unit=='PASS 46 checks',unit
oracle=read('evidence/oracle-tests.json')
assert oracle['total']==oracle['passed']==98 and not oracle['original_elf_executed']
build=read('evidence/build.json')
for item in build['outputs']:assert sha(Path(item['Path']))==item['Hash'].lower()
elfs=[]
for path in sorted((ROOT/'build/android-arm64').iterdir()):
    b=path.read_bytes()
    assert b[:5]==b'\x7fELF\x02' and int.from_bytes(b[18:20],'little')==183
    elfs.append(path.name)

links=[]
for path in [ROOT/'README.md',ROOT/'REPORT.zh-CN.md',ROOT/'evidence/INDEX.md']:
    text=path.read_text(encoding='utf-8')
    for rel in re.findall(r'\]\(([^)]+)\)',text):
        if '://' in rel:continue
        assert (path.parent/rel).exists(),f'broken link: {path}: {rel}'
        links.append(rel)
# Check every plain JSON/ASM reference listed in the index.
index=(ROOT/'evidence/INDEX.md').read_text(encoding='utf-8')
refs=set(re.findall(r'(?<![A-Za-z0-9_/])(?:prior/|prior-fresh/)?[A-Za-z0-9_-]+\.json',index))
for rel in refs:
    if rel=='manifest.json':continue
    if rel=='verification.json':continue
    assert (ROOT/'evidence'/rel).exists(),f'missing indexed evidence: {rel}'

now=datetime.now(timezone(timedelta(hours=8))).isoformat()
verification=dict(timestamp=now,status='PASS',protected_files_unchanged=len(after),
    constants_checked=5,host_unit_checks=46,independent_oracle_checks=98,
    android_elfs=elfs,android_executed=False,original_elf_executed=False,
    evidence_references_checked=len(refs),document_links_checked=len(links),
    method='Saved IDA evidence and C++/Python verification, not original-ELF differential execution')
(ROOT/'evidence/verification.json').write_text(json.dumps(verification,indent=2),encoding='utf-8')
files=[]
for path in sorted(ROOT.rglob('*')):
    if not path.is_file() or path.suffix in {'.id0','.id1','.id2','.nam','.til','.zip','.pyc'}:continue
    if path.name in {'manifest.json','delivery.json'}:continue
    files.append(dict(path=path.relative_to(ROOT).as_posix(),size=path.stat().st_size,sha256=sha(path)))
manifest=dict(timestamp=now,sample_sha256=after[0]['Hash'],files=files)
(ROOT/'manifest.json').write_text(json.dumps(manifest,indent=2),encoding='utf-8')
archive=ROOT/'prism-mcp-clock-deliverables.zip'
with zipfile.ZipFile(archive,'w',zipfile.ZIP_DEFLATED) as z:
    for item in files:
        if item['path'].endswith('.i64'):continue
        z.write(ROOT/item['path'],item['path'])
    z.write(ROOT/'manifest.json','manifest.json')
with zipfile.ZipFile(archive) as z:assert z.testzip() is None
delivery=dict(archive=archive.name,sha256=sha(archive),size=archive.stat().st_size,
              excluded=['prism-mcp-clock.i64 (available separately in workspace)','original sample'],
              manifest_entries=len(files))
(ROOT/'delivery.json').write_text(json.dumps(delivery,indent=2),encoding='utf-8')
print(json.dumps(dict(verification=verification,delivery=delivery),ensure_ascii=False,indent=2))
