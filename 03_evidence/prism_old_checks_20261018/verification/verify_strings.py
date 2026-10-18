import json
from pathlib import Path
from bounded_strings import Fixture
root=Path(__file__).resolve().parents[1]
rows=json.loads((root/'strings.json').read_text())
for row in rows:
 f=Fixture();a=f.run(int(row['getter']['function'],16));assert a['reason']=='return'
 b=f.run(int(row['converter']['function'],16),[int(a['result'],16)]);assert b['reason']=='return'
 raw=bytes(f.u.mem_read(int(b['result'],16),256)).split(b'\0')[0].decode()
 assert raw==row['text'],(row['getter']['function'],raw,row['text'])
print('PASS:',len(rows),'original-instruction string getter/converter pairs')
