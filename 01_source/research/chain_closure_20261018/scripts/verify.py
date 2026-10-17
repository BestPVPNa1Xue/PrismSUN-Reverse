"""Inventory this reconstruction; never load or execute the original sample."""
from datetime import datetime, timezone
from pathlib import Path
import hashlib
import json
import re

ROOT = Path(__file__).resolve().parents[1]
RESEARCH = ROOT.parent
EVIDENCE = ROOT / 'evidence'

def read(path):
    return json.loads(path.read_text(encoding='utf-8-sig'))

def write(path, value):
    path.write_text(json.dumps(value, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')

def digest(path):
    with path.open('rb') as file:
        return hashlib.file_digest(file, 'sha256').hexdigest()

def record(path):
    return {'path': str(path), 'size': path.stat().st_size, 'sha256': digest(path)}

before = read(EVIDENCE / 'protected-before.json')
after = []
for item in before:
    observed = record(Path(item['path']))
    observed['unchanged'] = observed['sha256'] == item['sha256'] and observed['size'] == item['size']
    after.append(observed)
write(EVIDENCE / 'protected-after.json', after)
protected_changes = [item for item in after if not item['unchanged']]

core = read(EVIDENCE / 'host-tests.json')
jni = read(EVIDENCE / 'jni-tests.json')
assert core['passed'] and core['checks'] == 112
assert jni['passed'] and jni['checks'] == 10
build = read(EVIDENCE / 'build.json')
artifact_checks = []
for item in build['outputs']:
    ok = digest(Path(item['Path'])).lower() == item['Hash'].lower()
    artifact_checks.append({'path': item['Path'], 'matches_build_record': ok})
assert all(item['matches_build_record'] for item in artifact_checks)

links = []
for md in (ROOT/'README.md', ROOT/'REPORT.zh-CN.md', ROOT/'CHAIN_NOTES.zh-CN.md'):
    for target in re.findall(r'\[[^\]]*\]\(([^)]+)\)', md.read_text(encoding='utf-8')):
        if '://' in target or target.startswith('#'):
            continue
        path = (md.parent / target.split('#')[0]).resolve()
        # Generated below; these references are checked by exact target identity.
        exists = path.exists() or path in {(EVIDENCE/'verification.json').resolve(),
                                           (ROOT/'manifest.json').resolve()}
        links.append({'document': md.name, 'target': target, 'exists': exists})
assert all(link['exists'] for link in links), 'Broken document link'

dependencies = [
    RESEARCH/'environment_memory/src/environment_memory.hpp',
    RESEARCH/'environment_memory/src/environment_memory.cpp',
    RESEARCH/'src/observed_models.h', RESEARCH/'src/observed_models.cpp',
    RESEARCH/'accessibility/src/accessibility_env.hpp',
    RESEARCH/'accessibility/src/accessibility_env.cpp',
]
excluded = {'manifest.json', 'verification.json', 'prism-chain-closure.i64'}
files = [p for p in ROOT.rglob('*') if p.is_file() and p.name not in excluded
         and p.suffix not in {'.id0', '.id1', '.id2', '.nam', '.til', '.pyc'}]
manifest = {'scope': 'final snapshot; excludes manifest itself, verification, active IDB and live IDA working files; immutable .snapshot.i64 included',
            'files': [record(p) for p in sorted(files)],
            'reused_source_dependencies': [record(p) for p in dependencies]}
write(ROOT/'manifest.json', manifest)
verification = {
    'verified_at_utc': datetime.now(timezone.utc).isoformat(),
    'method': 'Single-agent serial IDA Pro MCP + local evidence; no REA',
    'sample_executed': False, 'original_instructions_emulated': False,
    'sample_bytes_patched': False, 'android_executed': False, 'apk_created': False,
    'idb_saved': 'D:/PrismSUN/research/chain_closure_20261018/prism-chain-closure.i64',
    'immutable_idb_snapshot': record(ROOT/'prism-chain-closure.snapshot.i64'),
    'idb_save_confirmed_by_tool': True, 'ida_auto_analysis_ready': False,
    'protected_files_unchanged': len(after) - len(protected_changes),
    'protected_files_changed': protected_changes, 'core_host_checks': core['checks'],
    'jni_mock_checks': jni['checks'], 'android_target': build['androidTarget'],
    'artifact_checks': artifact_checks, 'document_links': links,
    'manifest_files': len(manifest['files']), 'dependency_files': len(dependencies),
    'remaining': ['event20 state+16 post-construction provenance',
                  'event20 original error text and independent raw numeric scanner',
                  'runtime supplied class list / handler / status / maps',
                  'Android runtime equivalence; full transport and server semantics',
                  'other modules and common entry protection are not exhaustive here'],
    'code_and_build_checks_passed': True,
    'protected_file_check_passed': not protected_changes,
    'passed': not protected_changes,
}
write(EVIDENCE/'verification.json', verification)
print(json.dumps({k: verification[k] for k in ('passed','protected_files_unchanged',
      'core_host_checks','jni_mock_checks','manifest_files','dependency_files')}, ensure_ascii=False))
