"""Read-only deliverable/identity checks; does not rerun completed analysis."""
import hashlib
import json
import re
from pathlib import Path
from elftools.elf.elffile import ELFFile

ROOT = Path(__file__).resolve().parents[1]
def digest(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()
def read(name):
    return json.loads((ROOT / name).read_text(encoding='utf-8-sig'))

protected = []
for item in read('evidence/before.json'):
    actual = digest(item['Path'])
    protected.append({'path': item['Path'], 'before': item['Hash'].lower(), 'after': actual,
                      'unchanged': item['Hash'].lower() == actual})
assert all(x['unchanged'] for x in protected)

files = []
for name, key in [('build.json', 'sources_and_outputs'), ('jni-build-verification.json', 'files'),
                  ('jni-env-build-verification.json', 'files')]:
    for item in read('evidence/' + name)[key]:
        actual = digest(item['path'])
        files.append({'manifest': name, 'path': item['path'], 'sha256': actual, 'matched': actual == item['sha256']})
assert all(x['matched'] for x in files)
replay = read('evidence/core-final-replay.json')
assert replay['dll_sha256'] == digest(ROOT/'build/host/accessibility_core.dll')
assert replay['original_evidence_sha256'] == digest(ROOT/'evidence/core-differential.json')

links = []
for md in [ROOT/'REPORT.zh-CN.md', ROOT/'README.zh-CN.md']:
    for target in re.findall(r'\]\(([^)]+)\)', md.read_text(encoding='utf-8')):
        if '://' in target or target.startswith('#'): continue
        path = md.parent / target.split('#')[0]
        links.append({'source': md.name, 'target': target, 'exists': path.exists()})
assert all(x['exists'] for x in links)

with (ROOT/'build/android-arm64/libaccessibility_reconstruction.so').open('rb') as stream:
    elf = ELFFile(stream)
    symbols = [s.name for s in elf.get_section_by_name('.dynsym').iter_symbols() if s['st_shndx'] != 'SHN_UNDEF']
    architecture = {'class': elf.elfclass, 'machine': elf['e_machine'], 'type': elf['e_type'],
                    'needed': [t.needed for t in elf.get_section_by_name('.dynamic').iter_tags() if t['d_tag'] == 'DT_NEEDED'],
                    'api_symbols': [s for s in symbols if any(x in s for x in ['observe_vm', 'a11y_', 'enumerate_enabled', 'ScopedJniEnvironment'])]}
assert architecture['class'] == 64 and architecture['machine'] == 'EM_AARCH64'
assert any('observe_vm' in s for s in architecture['api_symbols'])
assert 'a11y_evaluate' in architecture['api_symbols']
assert 'libc++_shared.so' not in architecture['needed'] # bundled static libc++

summary = {'status': 'PASS', 'protected': protected, 'manifest_files': files,
           'document_links': links, 'android_artifact': architecture,
           'final_core_replay': replay,
           'rea_session_closed': read('evidence/rea/summary.json')['passed'],
           'new_database_sha256': digest(ROOT/'prism-accessibility.i64'),
           'limitations': ['No Android device runtime', 'Scheduler interval and server policy not recovered',
                           'JNI adapter adds explicit exception/null checks; no ABI/OOM/concurrency equivalence claim']}
(ROOT/'evidence/final-verification.json').write_text(json.dumps(summary, indent=2), encoding='utf-8')
print(json.dumps({'status': 'PASS', 'protected_files': len(protected), 'manifest_entries': len(files),
                  'document_links': len(links), 'android_machine': architecture['machine'],
                  'hash_cases': replay['original_hash_cases'], 'consumer_cases': replay['consumer_cases']}))
