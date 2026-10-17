#!/usr/bin/env python3
"""Create a categorized, byte-preserving local Prism research delivery."""
import argparse
import collections
import csv
import datetime as dt
import hashlib
import io
import json
import os
from pathlib import Path, PurePosixPath
import re
import shutil
import subprocess
import sys
from urllib.parse import unquote
import zipfile

from verify_bundle import verify


def sha(path):
    with path.open('rb') as f:
        return hashlib.file_digest(f, 'sha256').hexdigest()


def json_text(value):
    return json.dumps(value, ensure_ascii=False, indent=2) + '\n'


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--workspace', type=Path, default=Path(__file__).resolve().parents[2])
    parser.add_argument('--name', default='PrismSUN-research-20261018')
    args = parser.parse_args()
    ws = args.workspace.resolve()
    if not re.fullmatch(r'[A-Za-z0-9_-]+', args.name):
        raise ValueError('Bundle name must be a simple directory name')
    out = ws / 'dist' / args.name
    zip_path = out.with_suffix('.zip')
    if out.exists() or zip_path.exists():
        raise ValueError('Delivery already exists; choose a new --name, never overwrite a delivery')
    out.mkdir(parents=True)
    origin_map, records, report_views, exclusions = {}, {}, {}, []
    scanned = []
    doc_origins = []

    def write(rel, content, **metadata):
        p = out / rel
        if p.exists():
            raise ValueError('Duplicate output: ' + rel)
        p.parent.mkdir(parents=True, exist_ok=True)
        p.write_text(content, encoding='utf-8', newline='\n')
        records[rel] = {'kind': 'generated', **metadata}

    def copy(src, rel, restore=None, kind='original'):
        if rel in records:
            raise ValueError('Duplicate archive path: ' + rel)
        dest = out / rel
        dest.parent.mkdir(parents=True, exist_ok=True)
        before = src.stat()
        source_hash = sha(src)
        shutil.copy2(src, dest)
        after = src.stat()
        if before.st_size != after.st_size or before.st_mtime_ns != after.st_mtime_ns:
            raise ValueError('Source changed during copy: ' + str(src))
        if sha(dest) != source_hash or sha(src) != source_hash:
            raise ValueError('Copy verification failed: ' + str(src))
        source_rel = src.relative_to(ws).as_posix()
        records[rel] = {'kind': kind, 'source_path': source_rel, 'source_sha256': source_hash,
                        'source_mtime_ns': after.st_mtime_ns}
        if restore:
            records[rel]['restore_path'] = restore
            if restore in origin_map:
                raise ValueError('Duplicate original path: ' + restore)
            origin_map[restore] = rel

    def classify_research(p):
        rel = p.relative_to(ws).as_posix()
        sub = p.relative_to(ws / 'research')
        parts = sub.parts
        if '__pycache__' in parts or p.suffix in ('.pyc', '.pyo'):
            return None, 'Python bytecode cache'
        if p.suffix.lower() in ('.id0', '.id1', '.id2', '.nam', '.til'):
            return None, 'Transient IDA working file; saved .i64 retained'
        if parts[:2] == ('tooling', 'rea'):
            return '08_history/legacy_tooling/' + rel, 'historical_tooling'
        if p.suffix.lower() in ('.i64', '.idb'):
            return '05_ida_databases/' + rel, 'ida_database'
        if p.suffix.lower() == '.zip':
            return '08_history/previous_archives/' + rel, 'previous_archive'
        if p.suffix.lower() == '.md':
            return '03_evidence/original_documents/' + rel, 'original_document'
        if 'build' in parts:
            return '04_binaries/' + rel, 'historical_build'
        if any(x in parts for x in ('src', 'tests', 'scripts', 'aggregate')) or p.name in ('CMakeLists.txt', '.clang-format'):
            return '01_source/' + rel, 'reconstruction_source'
        return '03_evidence/' + rel, 'research_evidence'

    for src in sorted((ws / 'research').rglob('*')):
        if not src.is_file():
            continue
        rel = src.relative_to(ws).as_posix()
        scanned.append(rel)
        dest, kind = classify_research(src)
        if dest is None:
            exclusions.append({'path': rel, 'reason': kind})
            continue
        copy(src, dest, rel, kind)
        if kind == 'original_document':
            report_views[rel] = '02_reports/' + rel
            doc_origins.append(rel)
    for name, category in [('libprism-sun.so', '06_samples/'), ('libprism-sun.so.i64', '05_ida_databases/original/')]:
        copy(ws / name, category + name, name, 'original_sample' if name.endswith('.so') else 'original_idb')
    sample_hash = records['06_samples/libprism-sun.so']['source_sha256']
    if sample_hash != '92e7d4adda7e222aa9dce389009a186adabb2602b80d618d417e0f6d509adaf4':
        raise ValueError('Unexpected Prism sample identity')

    public = ws / 'PrismDetector-public'
    git_commit = subprocess.check_output(['git', 'rev-parse', 'HEAD'], cwd=public, text=True).strip()
    files = subprocess.check_output(['git', 'ls-files', '-z'], cwd=public).decode().strip('\0').split('\0')
    with zipfile.ZipFile(ws / 'PrismDetector/dist/PrismDetector-1.2.0-source.zip') as z:
        for f in files:
            src = public / f
            if z.read('PrismDetector/' + f) != src.read_bytes():
                raise ValueError('Published app source no longer matches delivered ZIP: ' + f)
            copy(src, '07_application/PrismDetector/source/' + f, 'PrismDetector/' + f, 'published_app_source')
    for src in sorted((ws / 'PrismDetector/evidence').rglob('*')):
        if not src.is_file() or '__pycache__' in src.parts:
            continue
        rel = src.relative_to(ws).as_posix()
        suffix = src.relative_to(ws / 'PrismDetector/evidence').as_posix()
        if src.suffix == '.i64':
            dest = '05_ida_databases/application_reference/' + rel
        elif src.suffix == '.dex':
            dest = '06_samples/application_reference/' + rel
        else:
            dest = '07_application/PrismDetector/evidence/' + suffix
        copy(src, dest, rel, 'app_evidence')
    for src in sorted((ws / 'PrismDetector/dist').iterdir()):
        if not src.is_file():
            continue
        rel = src.relative_to(ws).as_posix()
        if '1.0.0' in src.name or '1.1.0' in src.name:
            dest = '08_history/application_releases/' + src.name
        else:
            dest = '07_application/PrismDetector/release-1.2.0/' + src.name
        copy(src, dest, rel, 'app_release')
    for name in ['README.zh-CN.md', 'build-1.2.0-log.txt']:
        src = ws / 'PrismDetector' / name
        if src.exists():
            copy(src, '07_application/PrismDetector/local_notes/' + name, 'PrismDetector/' + name, 'app_local_record')
    old_package = ws / 'dist/PrismSUN-reconstruction-source.zip'
    if old_package.exists():
        copy(old_package, '08_history/previous_archives/PrismSUN-reconstruction-source.zip', 'dist/PrismSUN-reconstruction-source.zip', 'previous_archive')
    for name in ['package_prism_research.py', 'verify_bundle.py', 'restore_workspace.py']:
        copy(Path(__file__).resolve().parent / name, '09_tools/' + name, kind='delivery_tool')

    # Readable reports get portable hyperlinks; the byte-exact originals remain evidence.
    link_audit = []
    link_pattern = re.compile(r'(?<=\]\()([^\r\n)]+)(?=\))')
    workspace_prefix = ws.as_posix().lower().rstrip('/') + '/'

    def resolve_original(target, doc):
        value = unquote(target.strip('<>')).replace('\\', '/')
        if value.lower().startswith(workspace_prefix):
            return value[len(workspace_prefix):]
        if re.match(r'^[A-Za-z]:/', value):
            return None
        return os.path.normpath(str(PurePosixPath(doc).parent / value)).replace('\\', '/')

    for original in doc_origins:
        raw = (out / origin_map[original]).read_text(encoding='utf-8-sig')
        dest = report_views[original]

        def rewrite(match):
            full = match.group(1)
            if re.match(r'^(https?://|mailto:|codex:|#)', full, re.I):
                return full
            target, marker, fragment = full.partition('#')
            origin = resolve_original(target, original)
            mapped = report_views.get(origin, origin_map.get(origin))
            if mapped:
                replacement = os.path.relpath(out / mapped, (out / dest).parent).replace('\\', '/')
                link_audit.append({'document': original, 'original_target': full, 'status': 'rewritten', 'target': mapped})
                return replacement + (marker + fragment if marker else '')
            # Local directory links can be ambiguous after classification; use the file index.
            link_audit.append({'document': original, 'original_target': full, 'status': 'historical_unresolved'})
            index = os.path.relpath(out / '00_guide/FILE_INDEX.csv', (out / dest).parent).replace('\\', '/')
            return index

        rendered = link_pattern.sub(rewrite, raw)
        original_link = os.path.relpath(out / origin_map[original], (out / dest).parent).replace('\\', '/')
        banner = f'> 归档阅读副本：只调整文件超链接；原文、代码块中的历史路径与结论保持原样。[逐字节原始文件]({original_link})。历史失效链接转到文件索引，原目标见 `00_guide/report-link-audit.json`。\n\n'
        write(dest, banner + rendered, kind='report_reading_copy', derived_from=original)

    # Historical manifests remain unchanged; compare their expectations with current files.
    audits = []
    manifest_specs = [
        ('research/chain_closure_20261018/manifest.json', 'research/chain_closure_20261018'),
        ('research/mcp_clock/manifest.json', 'research/mcp_clock'),
        ('research/environment_memory/manifest.json', ''),
        ('research/device_identity/evidence/manifest.json', 'research/device_identity'),
    ]
    for original, base in manifest_specs:
        data = json.loads((out / origin_map[original]).read_text(encoding='utf-8-sig'))
        entries = list(data.get('files', [])) + list(data.get('reused_source_dependencies', []))
        if isinstance(data.get('sha256'), dict):
            entries += [{'path': k, 'sha256': v} for k, v in data['sha256'].items()]
        rows = []
        for e in entries:
            p = str(e['path']).replace('\\', '/')
            if p.lower().startswith(workspace_prefix):
                p = p[len(workspace_prefix):]
            elif not p.startswith('research/'):
                p = (PurePosixPath(base) / p).as_posix()
            archived = origin_map.get(p)
            actual = records[archived]['source_sha256'] if archived else None
            rows.append({'source_path': p, 'archived_path': archived, 'expected': e['sha256'], 'actual': actual,
                         'status': 'match' if actual == e['sha256'] else ('not_in_current_snapshot' if actual is None else 'mismatch')})
        audits.append({'manifest': original, 'counts': dict(collections.Counter(r['status'] for r in rows)), 'entries': rows})
    write('00_guide/historical-manifest-audit.json', json_text(audits))
    audit_summary = ['# 历史清单复核', '', '这张表比较历史记录与本次读取到的文件；归档拷贝校验使用另一份新清单，二者不混为一项验收。', '',
                     '| 历史 manifest | 匹配 | 不匹配 | 当前快照中缺失 |', '| --- | ---: | ---: | ---: |']
    for a in audits:
        counts = a['counts']
        audit_summary.append(f'| `{a["manifest"]}` | {counts.get("match", 0)} | {counts.get("mismatch", 0)} | {counts.get("not_in_current_snapshot", 0)} |')
    audit_summary += ['', '四链 191 项含 185 项产物和 6 项复用源码依赖。历史 environment 数据库保护异常仍以四链 verification 为准，不因四链 manifest 对其交付快照匹配而消失。', '']
    for a in audits:
        for e in a['entries']:
            if e['status'] != 'match':
                audit_summary += [f'## `{e["source_path"]}`', '', f'- 历史值：`{e["expected"]}`', f'- 当前值：`{e["actual"]}`',
                                  f'- 状态：`{e["status"]}`。', '', '本次只读取并保存当前文件；归档前后源文件哈希一致。现有比较不能证明历史变化的原因或只是数据库元数据变化。旧 manifest 和当前数据库均保留。', '']
    audit_summary += ['完整逐文件结果：[historical-manifest-audit.json](historical-manifest-audit.json)。', '']
    write('00_guide/HISTORICAL_MANIFEST_AUDIT.zh-CN.md', '\n'.join(audit_summary))
    write('00_guide/report-link-audit.json', json_text(link_audit))
    write('00_guide/EXCLUSIONS.json', json_text({'excluded_research_files': exclusions,
          'outside_scope': ['Android SDK/NDK/AVD and build caches', 'Signing private keys and keystores',
                            'Unrelated tool installations', 'User input APKs outside the selected research and evidence trees',
                            'Git object database; published app source commit is recorded separately'],
          'historical_REA_records': 'Existing historical records are preserved as provenance; no REA tools were invoked by packaging.'}))

    # Confirm the C++ include closure after relocation; system headers are toolchain inputs.
    source_root = out / '01_source/research'
    include_dirs = sorted({p.parent for p in source_root.rglob('*') if p.is_file() and p.suffix in ('.h', '.hpp')})
    include_rows = []
    for p in sorted(source_root.rglob('*')):
        if p.suffix not in ('.cpp', '.h', '.hpp', '.c'):
            continue
        for name in re.findall(r'^\s*#\s*include\s*"([^"]+)"', p.read_text(encoding='utf-8-sig'), re.M):
            candidates = [p.parent / name] + [d / name for d in include_dirs]
            found = next((q.resolve() for q in candidates if q.is_file()), None)
            include_rows.append({'file': p.relative_to(out).as_posix(), 'include': name,
                                 'resolved': found.relative_to(out).as_posix() if found else None})
    if any(e['resolved'] is None for e in include_rows):
        raise ValueError('Unresolved quoted C++ includes: ' + str([e for e in include_rows if not e['resolved']]))
    write('00_guide/source-include-check.json', json_text({'result': 'PASS', 'checked': len(include_rows),
          'scope': 'Quoted local C/C++ include existence; not a compiler or runtime test', 'entries': include_rows}))

    modules = [
        ('四链最新重建', 'chain_closure_20261018', 'TracerPid、seccomp/SIGSYS、maps/四库组合、event22', '112 项宿主核心 + 10 项 JNI mock；ARM64/API24 交叉编译', 'event20 仍部分重建；原库 ABI、真实输入与 Android 等价未证'),
        ('环境与内存', 'environment_memory', '四库 ELF/CRC 比较器、环境循环、输入法 JNI', '专项原始测试/差分及构建记录', 'maps/Tracer/SIGSYS 的新入口以四链模块为准'),
        ('无障碍', 'accessibility', '枚举、排序/hash、变化状态机、JNI 生命周期', '专属原指令/重建对照与 mock 记录', '原链没有据此证明 KeyMapper 专用作弊规则'),
        ('设备身份', 'device_identity', '设备/应用字段、摘要、密码与 Android 适配', '专项 manifest、verification 与差分证据', '证书摘要对象与官方签名信任不是同一件事'),
        ('MCP 与时钟', 'mcp_clock', 'MCP 文件链、时钟输入、RNG/HMAC_DRBG', '46 项宿主检查；独立 HMAC 对照 98/98（历史记录）', '原时钟链为 RNG 支持；北京时间校对属于应用新增功能'),
    ]

    def report_link(module, name='REPORT.zh-CN.md'):
        return '../02_reports/research/' + (module + '/' if module else '') + name

    table = ['| 模块 | 代码 | 报告 | 证据 | 状态与边界 |', '| --- | --- | --- | --- | --- |']
    for label, module, scope, tests, limit in modules:
        report_name = 'REPORT.zh-CN.md'
        table.append(f'| {label} | [src](../01_source/research/{module}/src/) | [报告]({report_link(module, report_name)}) | [evidence](../03_evidence/research/{module}/evidence/) | {scope}；{tests}；{limit} |')
    table.append('| 基础模型 | [src](../01_source/research/src/) | [历史总报告](../02_reports/research/REPORT.zh-CN.md) | [原始证据](../03_evidence/research/evidence/) | 入口指令分类、观察策略、类探测、共享 ring；四链不等于全库覆盖 |')
    write('00_guide/MODULE_MAP.zh-CN.md', '# 模块、源码、报告与证据对照\n\n' + '\n'.join(table) + '\n\n任务 ID 与事件 ID 不可混用；接口和真实输入的边界以最新专项报告为准。\n')
    write('00_guide/ARCHITECTURE.zh-CN.md', '''# 源码架构与阅读顺序

原样本 `libprism-sun.so` 提供静态逆向依据；`01_source/research` 是 C++17 语义重建，`07_application` 是使用部分重建能力的独立 Android 检测应用。反编译 `.c` 在证据目录，不能当作可编译的重建源码。

```mermaid
flowchart TD
  Evidence[原样本 / IDA 数据库 / 原指令导出] --> Models[基础语义模型 research/src]
  Evidence --> Env[environment_memory / 四库与输入法]
  Evidence --> Access[accessibility / JNI 环境与无障碍]
  Evidence --> Identity[device_identity / 身份与摘要]
  Evidence --> Clock[mcp_clock / 文件与 RNG 时钟]
  Models --> Chains[chain_closure_20261018 / 最新四链]
  Env --> Chains
  Access --> Chains
  Chains --> App[PrismDetector 1.2.0 / C++ 检测与 Ruru UI]
  Env --> App
  Access --> App
  Identity --> App
```

四链模块复用 `environment_memory/src/environment_memory.*`、`src/observed_models.*` 与 `accessibility/src/accessibility_env.*`。这些目录之间的相对位置保持原样；每个模块的 `src`、`tests`、`scripts` 仍在一起。

`research/aggregate` 及 `build_all_detections.ps1` 是历史聚合工程，其已存 SO 没有纳入新四链源码。最新四链产物为 `04_binaries/research/chain_closure_20261018/build/android-arm64/libprism_chains.so`。两者都不是原插件的 ABI 替代品。

先读 [当前状态](CURRENT_STATUS.zh-CN.md)，再读 [模块对照](MODULE_MAP.zh-CN.md)，随后阅读相应报告、源码和证据。完整文件树在 [TREE.txt](TREE.txt)，旧路径到归档位置在 [FILE_INDEX.csv](FILE_INDEX.csv)。
''')
    write('00_guide/CURRENT_STATUS.zh-CN.md', f'''# 当前状态与历史边界

归档日期：2026-10-18；原样本 SHA-256：`{sample_hash}`。

最新研究顺序：基础研究 → 无障碍/设备身份 → 环境内存 → MCP/时钟 → 覆盖审计 → 四链闭合 → 调试 APK 评估 → PrismDetector 1.0/1.1/1.2。历史报告中的“还没有 APK”“尚未厘清”等字样保持原文；判断现状时应按此顺序参照。

- [四链报告]({report_link('chain_closure_20261018')}) 是 TracerPid、seccomp/SIGSYS、maps 过滤及 event22 的最新研究入口。112/10 是宿主模型/mock 检查，不是全库覆盖率或设备检出率。
- event20 的 `state+16` 后续来源、原始错误文字及独立 raw 数字 scanner 仍未闭合；真实类名单、handler、status/maps 属于外部输入。宿主门控、全库自检覆盖、完整网络/服务端语义仍有边界。
- 原始四链 `verification.json` 保留 `passed=false`：5 个保护文件中 4 个匹配，历史 `prism-environment-memory.i64` 哈希变化。不能证明只是元数据变化。本归档不会修改此判定，也不会把新的文件拷贝校验解释为旧异常已解决。
- 本次逐项复查历史 manifest，结果保存在 [历史清单复核](HISTORICAL_MANIFEST_AUDIT.zh-CN.md)。另发现 MCP/时钟数据库当前哈希与旧 manifest 不一致；其余三份清单的条目匹配。旧值、现值和原始文件均保留，不能推断变化原因。旧清单与本次归档校验分别记录。
- PrismDetector 1.2.0 已发布，提交 `{git_commit}`。应用采用 Ruru UI，包含用户指定的 KeyMapper 特征、Minecraft 包体积/证书基准和北京时间校对。这些应用规则与原 Prism 已证明的规则分开看待；MCP 文件检测没有接入应用。
- 应用的 API34 x86_64 验收见 [1.2.0 记录](../07_application/PrismDetector/evidence/v1.2.0/VALIDATION.zh-CN.md)。ARM64 真机和 API35 未实测。这个应用验收不意味着原 Prism 全链已经完成 Android 对照。

旧 REA 证据只是已有历史来源，保留原文件与来源名称；本次整理未调用 REA 或执行逆向分析，也没有重跑原样本、原指令仿真或 Android 产物。
''')
    write('00_guide/BUILD_AND_RESTORE.zh-CN.md', r'''# 校验、恢复与构建入口

需要 Python 3.11 或更新版本。解压后先运行只读校验：

```powershell
python .\09_tools\verify_bundle.py .
```

也可以直接校验 ZIP：`python verify_bundle.py PrismSUN-research-20261018.zip`。校验逐个读取所有文件，检查清单、大小、SHA-256，并由 ZIP reader 检查 CRC；不会加载或运行归档中的 SO/EXE/IDA 数据库。

分类后的代码位于 `01_source/research`，源码内部的模块相对路径保持。为使历史脚本的 `evidence`/`build` 输出与报告布局都恢复一致，推荐复制到一个新的工作目录：

```powershell
python .\09_tools\restore_workspace.py --output D:\PrismSUN-restored --scope research-source
```

`research-source` 只恢复源码、测试和构建/分析脚本；`research` 还原全部研究文档、原始证据、已存产物、原样本和 IDA 数据库；`all` 额外还原应用及历史发布包。`--dry-run` 校验将要恢复的输入而不复制。目标必须不存在，不覆盖原工作区。阅读副本不参加恢复，恢复的是逐字节原始文档。

最新四链的历史构建入口（由使用者在恢复后按需执行，本次打包未重跑）：

```powershell
Set-Location D:\PrismSUN-restored
& .\research\chain_closure_20261018\scripts\build.ps1 -HostCompiler 'C:\path\to\g++.exe' -Ndk 'C:\path\to\android-ndk'
```

该脚本运行宿主测试并交叉编译 Android ARM64/API24，不执行原 SO。其余模块入口在各自 `scripts/build.ps1` 和 README。历史分析脚本可能写死原工作区、工具链路径或依赖 Unicorn/IDA；保留它们用于追溯，不把全部脚本声明为解压即运行。分析脚本与重建源码构建不是同一流程。

旧聚合构建入口 `research/scripts/build_all_detections.ps1` 尚未合入四链，不用它代表最新模块。应用源码在 `07_application/PrismDetector/source`，构建遵循其中 README；签名私钥和 SDK/NDK 工具链不在包内。

原始文档和历史 JSON 中的绝对路径属于取证内容，未改写。阅读副本只改 Markdown 文件链接；不能解析的旧链接转到 FILE_INDEX.csv，并在 report-link-audit.json 中保留原目标。
''')
    write('README.zh-CN.md', '''# PrismSUN 研究与重建成果归档 · 2026-10-18

本包整理最新 Prism C++ 重建、历史与最新报告、逆向原始证据、IDA 数据库、样本、构建产物，以及 PrismDetector 1.2.0 应用源码和验收记录。

| 目录 | 内容 |
| --- | --- |
| `00_guide/` | 当前状态、架构、模块对照、文件索引、完整目录树与审计结果 |
| `01_source/research/` | 重建 C++、测试、构建和分析脚本；保留模块相对依赖 |
| `02_reports/research/` | 可点击导航的报告阅读副本，仅修正链接 |
| `03_evidence/` | 原始证据、反编译导出、历史 manifest，以及字节不变的原始报告 |
| `04_binaries/` | 历史构建的 Windows/Android 产物与构建记录 |
| `05_ida_databases/` | 原始 IDB、各专项数据库、最新四链交付快照及应用参考数据库 |
| `06_samples/` | 原始 Prism SO 与已有 UI 参考 DEX |
| `07_application/` | PrismDetector 1.2.0 已发布源码、APK、验收和证书基准证据 |
| `08_history/` | 旧交付包、旧应用版本和历史工具安装证据 |
| `09_tools/` | 本次打包脚本、只读校验器、原布局恢复工具 |

从 [当前状态](00_guide/CURRENT_STATUS.zh-CN.md)、[架构说明](00_guide/ARCHITECTURE.zh-CN.md) 和 [模块对照](00_guide/MODULE_MAP.zh-CN.md) 开始。最新研究入口是四链闭合，历史总报告保留其原有时间背景。

`PACKAGE-MANIFEST.json` 逐文件记录 SHA-256、大小、来源和可恢复路径；`SHA256SUMS.txt` 还覆盖 manifest 自身。完整目录树见 [TREE.txt](00_guide/TREE.txt)。校验与构建入口见 [BUILD_AND_RESTORE](00_guide/BUILD_AND_RESTORE.zh-CN.md)。

本包是本地完整研究归档，包含历史路径、设备运行报告和分析数据库。GitHub 上的应用源码交付保持独立，仍是已经发布的 v1.2.0。

BEFORE：原始工作区及历史验证记录作为输入冻结读取。

AFTER：分类复制、可读报告导航、每文件校验和一个完整 ZIP；没有改写原研究文件。

ROLLBACK：无需回滚源文件；保留原工作区即可。恢复工具只写入新目录，不覆盖历史研究或发布标签。
''')

    # Source/evidence inventory and stable ordering.
    buf = io.StringIO(newline='')
    writer = csv.writer(buf)
    writer.writerow(['original_workspace_path', 'archive_path', 'reading_copy', 'kind', 'bytes', 'sha256'])
    for original, dest in sorted(origin_map.items()):
        p = out / dest
        writer.writerow([original, dest, report_views.get(original, ''), records[dest]['kind'], p.stat().st_size, records[dest]['source_sha256']])
    write('00_guide/FILE_INDEX.csv', '\ufeff' + buf.getvalue())
    groups = collections.defaultdict(lambda: {'files': 0, 'bytes': 0})
    for rel in records:
        g = groups[rel.split('/')[0]]
        g['files'] += 1
        g['bytes'] += (out / rel).stat().st_size
    known_anomalies = [{'manifest': a['manifest'], 'counts': a['counts']} for a in audits]
    write('00_guide/PACKAGING_AUDIT.json', json_text({
        'research_input_files': len(scanned), 'research_archived_originals': sum(p.startswith('research/') for p in origin_map),
        'research_excluded_files': len(exclusions), 'research_inventory_complete': len(scanned) == sum(p.startswith('research/') for p in origin_map) + len(exclusions),
        'original_copy_hashes_checked': True, 'original_sample_sha256': sample_hash,
        'app_source_files': len(files), 'app_source_commit': git_commit, 'app_source_matches_release_zip': True,
        'quoted_cpp_includes_resolved': len(include_rows), 'report_hyperlinks_rewritten': sum(r['status'] == 'rewritten' for r in link_audit),
        'historical_unresolved_links_preserved_in_audit': sum(r['status'] != 'rewritten' for r in link_audit),
        'historical_manifest_results': known_anomalies, 'category_totals_before_generated_indexes': groups,
        'sample_executed': False, 'reverse_engineering_tools_invoked': False, 'old_tests_rerun': False,
        'original_research_conclusions_changed': False, 'published_to_github': False,
    }))
    all_paths = sorted(list(records) + ['00_guide/TREE.txt', '00_guide/PORTABLE_LINK_CHECK.json', 'PACKAGE-MANIFEST.json', 'SHA256SUMS.txt'])
    tree = {}
    for path in all_paths:
        node = tree
        for part in PurePosixPath(path).parts:
            node = node.setdefault(part, {})

    def render(node, prefix=''):
        result = []
        items = sorted(node.items(), key=lambda kv: (not bool(kv[1]), kv[0]))
        for i, (name, children) in enumerate(items):
            last = i == len(items) - 1
            result.append(prefix + ('└── ' if last else '├── ') + name + ('/' if children else ''))
            result.extend(render(children, prefix + ('    ' if last else '│   ')))
        return result

    write('00_guide/TREE.txt', args.name + '/\n' + '\n'.join(render(tree)) + '\n')
    checked_links = 0
    for doc in [out / 'README.zh-CN.md', *(out / '00_guide').glob('*.md'), *(out / '02_reports').rglob('*.md')]:
        for target in re.findall(r'\]\(([^\r\n)]+)\)', doc.read_text(encoding='utf-8')):
            if re.match(r'^(https?://|mailto:|codex:|#)', target, re.I):
                continue
            local = target.split('#', 1)[0].strip('<>')
            if not (doc.parent / local).exists():
                raise ValueError(f'Broken delivery link: {doc} -> {target}')
            checked_links += 1
    write('00_guide/PORTABLE_LINK_CHECK.json', json_text({'result': 'PASS', 'local_links_checked': checked_links,
          'scope': 'Generated guide and readable research reports; original historical documents are preserved unchanged'}))
    # A final pass ensures no copied input changed while the package was being assembled.
    for rel, metadata in records.items():
        if 'source_path' in metadata:
            src = ws / metadata['source_path']
            if sha(src) != metadata['source_sha256']:
                raise ValueError('Input changed before sealing: ' + str(src))
    sealed = []
    for rel in sorted(records):
        p = out / rel
        sealed.append({'path': rel, 'bytes': p.stat().st_size, 'sha256': sha(p), **records[rel]})
    manifest = {'schema': 1, 'name': args.name, 'created_at_utc': dt.datetime.now(dt.timezone.utc).isoformat(),
                'scope': 'Local categorized research archive; source, reports, evidence, samples, databases and app delivery',
                'original_sample_sha256': sample_hash, 'app_version': '1.2.0', 'app_source_commit': git_commit,
                'file_count': len(sealed), 'files': sealed,
                'checksum_exclusions': ['PACKAGE-MANIFEST.json (covered by SHA256SUMS.txt)', 'SHA256SUMS.txt (self exclusion)']}
    (out / 'PACKAGE-MANIFEST.json').write_text(json_text(manifest), encoding='utf-8')
    sums = ''.join(e['sha256'] + '  ' + e['path'] + '\n' for e in sealed)
    sums += sha(out / 'PACKAGE-MANIFEST.json') + '  PACKAGE-MANIFEST.json\n'
    (out / 'SHA256SUMS.txt').write_text(sums, encoding='utf-8', newline='\n')
    print('Sealed:', len(sealed), 'payload files;', sum(e['bytes'] for e in sealed), 'bytes', flush=True)
    print('Historical audit:', json.dumps(known_anomalies, ensure_ascii=False), flush=True)
    with zipfile.ZipFile(zip_path, 'x', compression=zipfile.ZIP_DEFLATED, compresslevel=6, allowZip64=True) as z:
        paths = sorted(p for p in out.rglob('*') if p.is_file())
        for i, p in enumerate(paths, 1):
            z.write(p, args.name + '/' + p.relative_to(out).as_posix())
            if i % 300 == 0:
                print('Compressed', i, '/', len(paths), flush=True)
    result = verify(zip_path)
    result.update({'archive': zip_path.name, 'bytes': zip_path.stat().st_size, 'sha256': sha(zip_path),
                   'archive_entries': len(sealed) + 2, 'historical_manifest_audit_separate': True,
                   'source_workspaces_unmodified': True})
    result_path = zip_path.with_suffix('.verification.json')
    result_path.write_text(json_text(result), encoding='utf-8')
    zip_path.with_suffix('.zip.sha256').write_text(result['sha256'] + '  ' + zip_path.name + '\n', encoding='utf-8')
    print(json_text(result), flush=True)


if __name__ == '__main__':
    main()
