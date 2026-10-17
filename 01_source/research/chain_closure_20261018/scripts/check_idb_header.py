"""Read-only bounded hypothesis check; never writes a protected database.

Checks whether one flipped bit in the 128-byte header alone explains the
recorded hash change. A negative result does not locate other changed bytes.
"""
from pathlib import Path
import hashlib
import json

root=Path(__file__).resolve().parents[1]
item=next(x for x in json.loads((root/'evidence/protected-before.json').read_text())
          if x['path'].endswith('prism-environment-memory.i64'))
data=Path(item['path']).read_bytes()
view=memoryview(data)
result={'method':'SHA-256 comparison of in-memory single-bit variants of first 128 bytes',
        'input_sha256':hashlib.sha256(data).hexdigest(),'expected':item['sha256'],
        'protected_database_written':False,'matched':False,'tested':0}
for offset in range(min(128,len(data))):
    prefix=hashlib.sha256(view[:offset])
    for bit in range(8):
        h=prefix.copy()
        h.update(bytes([data[offset]^(1<<bit)]))
        h.update(view[offset+1:])
        result['tested']+=1
        if h.hexdigest()==item['sha256']:
            result.update(matched=True,offset=offset,before_byte=data[offset]^(1<<bit),
                          after_byte=data[offset])
            break
    if result['matched']:break
(root/'evidence/historical-idb-header-check.json').write_text(json.dumps(result,indent=2)+'\n')
print(json.dumps(result))
