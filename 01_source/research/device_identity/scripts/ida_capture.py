"""Sequential IDA Pro MCP capture, bound to this investigation's copied IDB."""
import argparse, json, urllib.request
from pathlib import Path
from static_probe import OUT, boundary, capture

p=argparse.ArgumentParser()
p.add_argument('addresses',nargs='+')
p.add_argument('--endpoint',default='http://127.0.0.1:1247/mcp')
p.add_argument('--tool',default='decompile',choices=['decompile','xrefs_to','callees'])
p.add_argument('--define',action='store_true')
a=p.parse_args()
def call(name,args):
    body=dict(jsonrpc='2.0',id=1,method='tools/call',params=dict(name=name,arguments=args))
    req=urllib.request.Request(a.endpoint,json.dumps(body).encode(),headers={'Content-Type':'application/json'})
    with urllib.request.urlopen(req,timeout=180) as r: raw=json.load(r)
    v=raw.get('result',{})
    d=v.get('structuredContent')
    if d is None:
        d=next((json.loads(t['text']) for t in v.get('content',[]) if t.get('type')=='text'),{})
    return raw,d
_,health=call('server_health',{})
assert Path(health['idb_path']).resolve()==(OUT/'prism-device-identity.i64').resolve(),health
assert health['hexrays_ready'],health
(OUT/'evidence/ida-health-latest.json').write_text(json.dumps(health,indent=2))
for address in a.addresses:
    addr=int(address,0); capture(addr)
    if a.define:
        f=boundary(addr)
        assert f and f['start']==addr,(address,f)
        raw,d=call('define_func',{'items':[{'addr':address,'end':hex(f['end'])}]})
        (OUT/f'evidence/define-{address}.json').write_text(json.dumps(raw,indent=2))
    args={'addr':address} if a.tool=='decompile' else {'addrs':[address],'limit':100}
    raw,d=call(a.tool,args)
    folder='decompiled' if a.tool=='decompile' else 'evidence'
    stem=address if a.tool=='decompile' else a.tool+'-'+address
    (OUT/f'{folder}/{stem}.json').write_text(json.dumps(raw,indent=2),encoding='utf-8')
    if a.tool=='decompile':
        code=d.get('code') or ''
        if code:(OUT/f'decompiled/{address}.c').write_text(code,encoding='utf-8')
        print(address,len(code),d.get('error',''))
    else:print(address,json.dumps(d))
