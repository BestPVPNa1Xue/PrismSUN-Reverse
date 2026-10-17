#!/usr/bin/env python3
"""Restore the original workspace-relative layout into a NEW directory."""
import argparse
import hashlib
import json
from pathlib import Path, PurePosixPath
import shutil


def safe(root, rel):
    p = PurePosixPath(rel)
    if p.is_absolute() or '..' in p.parts or '\\' in rel or ':' in rel:
        raise ValueError(f'Unsafe relative path: {rel}')
    result = (root / rel).resolve()
    if not result.is_relative_to(root.resolve()):
        raise ValueError(f'Path escapes target: {rel}')
    return result


def sha(path):
    with path.open('rb') as f:
        return hashlib.file_digest(f, 'sha256').hexdigest()


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--bundle', type=Path, default=Path(__file__).resolve().parents[1])
    parser.add_argument('--output', type=Path, required=True)
    parser.add_argument('--scope', choices=['research-source', 'research', 'all'], default='research-source')
    parser.add_argument('--dry-run', action='store_true')
    args = parser.parse_args()
    bundle, output = args.bundle.resolve(), args.output.resolve()
    if output.exists():
        raise SystemExit('Output already exists; choose a new directory. Nothing was overwritten.')
    if output.is_relative_to(bundle):
        raise SystemExit('Choose an output directory outside the archive directory.')
    manifest = json.loads((bundle / 'PACKAGE-MANIFEST.json').read_text(encoding='utf-8'))
    rows = [e for e in manifest['files'] if e.get('restore_path')]
    if args.scope == 'research-source':
        rows = [e for e in rows if e['path'].startswith('01_source/research/')]
    elif args.scope == 'research':
        rows = [e for e in rows if e['restore_path'].startswith('research/') or e['restore_path'] in ('libprism-sun.so', 'libprism-sun.so.i64')]
    seen = set()
    for e in rows:
        target = safe(output, e['restore_path'])
        if target in seen:
            raise ValueError(f'Duplicate destination: {target}')
        seen.add(target)
        if sha(safe(bundle, e['path'])) != e['sha256']:
            raise ValueError(f'Source digest mismatch: {e["path"]}')
    if not args.dry_run:
        output.mkdir(parents=True, exist_ok=False)
        for e in rows:
            target = safe(output, e['restore_path'])
            target.parent.mkdir(parents=True, exist_ok=True)
            shutil.copy2(safe(bundle, e['path']), target)
            if sha(target) != e['sha256']:
                raise ValueError(f'Restored digest mismatch: {target}')
        # Historical build scripts write to these folders but do not create them.
        for module in ('accessibility', 'device_identity', 'environment_memory', 'mcp_clock', 'chain_closure_20261018'):
            (output / 'research' / module / 'evidence').mkdir(parents=True, exist_ok=True)
        (output / 'research' / 'evidence').mkdir(parents=True, exist_ok=True)
    print(json.dumps({'result': 'PASS', 'scope': args.scope, 'files': len(rows),
                      'dry_run': args.dry_run, 'output': str(output),
                      'payloads_executed': False}, ensure_ascii=False, indent=2))
