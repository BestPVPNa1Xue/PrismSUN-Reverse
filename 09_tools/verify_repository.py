"""Check the published Git view. Use verify_bundle.py for the full release ZIP."""
import hashlib,json
from pathlib import Path
root=Path(__file__).resolve().parents[1]
manifest=json.loads((root/'REPOSITORY-MANIFEST.json').read_text(encoding='utf-8'))
for e in manifest['files']:
    p=root/e['path']
    with p.open('rb') as f: digest=hashlib.file_digest(f,'sha256').hexdigest()
    assert digest==e['sha256'] and p.stat().st_size==e['bytes'],e['path']
print('PASS:',len(manifest['files']),'published files verified')
