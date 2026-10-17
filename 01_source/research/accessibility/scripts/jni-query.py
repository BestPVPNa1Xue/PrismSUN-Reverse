"""Save complete read-only IDA MCP responses from the existing accessibility worker."""
import argparse
import json
import urllib.request
from pathlib import Path

p = argparse.ArgumentParser()
p.add_argument('addresses', nargs='+')
p.add_argument('--endpoint', default='http://127.0.0.1:47083/mcp')
a = p.parse_args()
out = Path('D:/PrismSUN/research/accessibility/evidence')
for index, address in enumerate(a.addresses):
    request = dict(jsonrpc='2.0', id=index+1, method='tools/call',
                   params=dict(name='decompile', arguments=dict(addr=address)))
    req = urllib.request.Request(a.endpoint, json.dumps(request).encode(),
                                 headers={'Content-Type':'application/json'})
    with urllib.request.urlopen(req, timeout=90) as r:
        response = json.load(r)
    (out / f'jni-decompile-{address}.json').write_text(json.dumps(response, indent=2), encoding='utf-8')
    result = response.get('result', {})
    s = result.get('structuredContent')
    if s is None:
        s = next((json.loads(t['text']) for t in result.get('content', []) if t.get('type')=='text'),{})
    code = s.get('code')
    if code:
        (out / f'jni-decompile-{address}.c').write_text(code, encoding='utf-8')
    print(address, len(code or ''), s.get('error',''))
