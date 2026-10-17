#!/usr/bin/env python3
"""Verify an extracted Prism research bundle or its ZIP, without executing payloads."""
import argparse
import hashlib
import json
from pathlib import Path, PurePosixPath
import zipfile


def safe_name(name):
    p = PurePosixPath(name)
    if p.is_absolute() or '..' in p.parts or '\\' in name or ':' in name:
        raise ValueError(f'Unsafe bundle path: {name}')
    return name


def digest_stream(stream):
    h = hashlib.sha256()
    for block in iter(lambda: stream.read(1024 * 1024), b''):
        h.update(block)
    return h.hexdigest()


def verify(target):
    archive = zipfile.ZipFile(target) if target.is_file() else None
    try:
        if archive:
            entries = [i.filename for i in archive.infolist() if not i.is_dir()]
            if len(entries) != len(set(entries)):
                raise ValueError('Duplicate ZIP entries')
            roots = {n.split('/')[0] for n in entries}
            if len(roots) != 1:
                raise ValueError('Expected one top-level directory')
            prefix = roots.pop() + '/'
            names = {safe_name(n[len(prefix):]) for n in entries}
            opener = lambda name: archive.open(prefix + safe_name(name))
        else:
            names = {p.relative_to(target).as_posix() for p in target.rglob('*') if p.is_file()}
            opener = lambda name: (target / safe_name(name)).open('rb')
        with opener('PACKAGE-MANIFEST.json') as f:
            manifest = json.load(f)
        files = manifest['files']
        expected = {safe_name(e['path']) for e in files}
        if len(expected) != len(files):
            raise ValueError('Duplicate manifest entries')
        if names != expected | {'PACKAGE-MANIFEST.json', 'SHA256SUMS.txt'}:
            raise ValueError(f'Inventory mismatch: missing={sorted(expected - names)}, extra={sorted(names - expected - {"PACKAGE-MANIFEST.json", "SHA256SUMS.txt"})}')
        with opener('SHA256SUMS.txt') as f:
            checksums = dict((line.split('  ', 1)[1], line.split('  ', 1)[0])
                             for line in f.read().decode('utf-8').splitlines() if line)
        if set(checksums) != expected | {'PACKAGE-MANIFEST.json'}:
            raise ValueError('Checksum inventory mismatch')
        with opener('PACKAGE-MANIFEST.json') as f:
            if digest_stream(f) != checksums['PACKAGE-MANIFEST.json']:
                raise ValueError('Manifest checksum mismatch')
        total = 0
        for e in files:
            with opener(e['path']) as f:
                actual = digest_stream(f)
            size = archive.getinfo(prefix + e['path']).file_size if archive else (target / e['path']).stat().st_size
            if actual != e['sha256'] or actual != checksums[e['path']] or size != e['bytes']:
                raise ValueError(f'Content mismatch: {e["path"]}')
            total += size
        return {'result': 'PASS', 'files_verified': len(files), 'payload_bytes': total,
                'inventory_exact': True, 'sha256_verified': True,
                'zip_crc_checked_while_reading': bool(archive), 'payloads_executed': False}
    finally:
        if archive:
            archive.close()


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('target', type=Path, nargs='?', default=Path(__file__).resolve().parents[1])
    args = parser.parse_args()
    print(json.dumps(verify(args.target.resolve()), ensure_ascii=False, indent=2))
