"""Extra input-shape and C-string boundaries in the unmodified event consumer."""
import json
from event_original import EventFixture, OUT

f = EventFixture()
rows = []
cases = [dict(challenge=b'12345678'), dict(challenge=b'1234567'),
         dict(challenge=b'1234567\0SUFFIX'), dict(challenge=b'12345678\0SUFFIX'),
         dict(item_count=0), dict(item_count=2), dict(item_type=8),
         dict(container_type=64), dict(ready=0, env_ok=False)]
for case in cases:
    row = f.consume(**case)
    rows.append(row)
    print(case, row['run']['reason'], row['observation']['kind'], flush=True)
    (OUT / 'evidence/event-boundaries-original.json').write_text(json.dumps(rows, indent=2))
    if row['run']['reason'] != 'returned' or not row['observation']['guard_ok']:
        raise SystemExit(1)
