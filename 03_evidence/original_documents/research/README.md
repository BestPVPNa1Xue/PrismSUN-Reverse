# PrismSUN Evidence And Reconstruction

This workspace contains an evidence-backed partial reconstruction of
`libprism-sun.so`, not a replacement anti-cheat module.

## Unified Android ARM64 Build And Source Package

The separate reconstruction modules can also be linked into one Android
ARM64 shared library. From the workspace root in PowerShell:

```powershell
& .\research\scripts\build_all_detections.ps1 -NdkRoot 'C:\path\to\android-ndk'
& .\research\scripts\package_source.ps1 -Force
```

The first command builds
`research/build/aggregate-android-arm64/libprismsun_reconstruction.so`
for `aarch64-linux-android24` and writes a SHA-256 build manifest beside it.
The second creates `dist/PrismSUN-reconstruction-source.zip`; it contains only
the classified aggregate-library source inputs, the final overall/specialized
reports, build entry/CMake project, final `.so`, and package/build manifests.
Tests, intermediate evidence, analysis/export scripts, demos, IDA databases,
original binaries, and old ZIP deliverables are excluded. The package manifest
records each included file's size and SHA-256. The aggregate source list and an
NDK CMake target are in `aggregate/CMakeLists.txt`.

This is a collection of independently reconstructed semantic models and
adapters. The combined library does not restore the original plugin ABI,
complete dispatch/network behavior, or integration with a game client/server;
cross-compilation is not an Android runtime test.

## Deliverables

- [2026-10-17 MCP 文件链与时钟链](mcp_clock/REPORT.zh-CN.md)：两遍 `/proc/<pid>/fd` 扫描、`MCPK` 头与 offset 24 文本、事件 32；时钟到 AutoSeeded_RNG/HMAC_DRBG 的完整本地消费链。[源码与构建](mcp_clock/README.md)。Windows 46 项检查和独立加密对照 98/98 通过，Android ARM64 两份 SO 已构建；仅 IDA Pro MCP 续接，没有继续上报链。

- [2026-10-16 环境、内存完整性与输入法专项](environment_memory/REPORT.zh-CN.md)：四库基线/比较、锁存状态、输入法列表与JNI、可编译源码；[构建说明](environment_memory/README.md)。仅IDAProMCP接续，未启用REA或子代理。

- [Chinese research report](REPORT.zh-CN.md)
- [Resume checkpoint](PROGRESS.md)
- `decompiled/`: address-tagged IDA Pro MCP pseudocode exports.
- `evidence/`: assembly pages, string-decoding results, manifests, and tests.
- `src/verified_helpers.*`: cyclic XOR and hexadecimal encoding helpers.
- `src/observed_models.*`: three predicates and a flag-update semantic model.
- `src/shared_ring_model.*`: stable-snapshot shared-ring read plan.
- `src/class_probe_model.*`: event-22 class selection and exception handling.
- `src/jni_layout_check.cpp`: compile-time NDK JNI table offset checks.
- `build/host/`: Windows test libraries and helper test executable.
- `build/android-arm64/`: Android AArch64 libraries targeting API 24.

## Verification Scope

| Evidence | Passed | Compared | Important exclusions |
| --- | ---: | --- | --- |
| `differential_helpers.json` | 169/169 | Original XOR/hex output and tail guards | Full plugin, Android runtime |
| `digest_decode_emulation.json` | 3/3 | Original SHA-256 name decoder | Actual digest implementation |
| `differential_models.json` | 524/524 | Two instruction slices and a reason function | Acquisition and JNI |
| `differential_policy.json` | 704/704 | Original flag-update control flow | Mocked status, SIGSYS, classifier, strings |
| `differential_shared_ring.json` | 648/648 | Original ring-reader control flow and call arguments | Payload copying, object ABI, concurrency |
| `differential_class_probe.json` | 404/404 | Original event-22 flow and four original JNI wrappers | Mocked configuration, JNI outcomes, acquisition, objects |

Each suite is a bounded fixture. Passing tests establish agreement for the
recorded cases and compared surfaces, not universal or full-module equivalence.
Build manifests include SHA-256 identities for sources and compiled artifacts.

## Reproduce A Changed Subset

Run from `D:\PrismSUN` in PowerShell. Build scripts skip outputs newer than
their input files. Inspect `PROGRESS.md` and existing manifests before resuming.

```powershell
& .\research\scripts\build_helpers.ps1
& .\research\scripts\build_observed_models.ps1
& .\research\scripts\build_shared_ring.ps1
& .\research\scripts\build_class_probe.ps1
& 'D:\Python 314\python.exe' .\research\scripts\test_differential.py
& 'D:\Python 314\python.exe' .\research\scripts\test_observed_models.py
& 'D:\Python 314\python.exe' .\research\scripts\test_filter_policy.py
& 'D:\Python 314\python.exe' .\research\scripts\test_shared_ring.py
& 'D:\Python 314\python.exe' .\research\scripts\test_class_probe.py
```

The historical 1024-byte XOR budget retry is documented in `PROGRESS.md` and
`differential_initial.json`; the final helper result is in
`differential_helpers.json`. Do not replace final results with an unexamined
initial run. Existing completed suites need no rerun during ordinary resume.

## Sample Identity

Original ELF SHA-256:
`92e7d4adda7e222aa9dce389009a186adabb2602b80d618d417e0f6d509adaf4`.

The original ELF and original i64 are preserved. IDA definitions are made only
in `prism-analysis.i64`. The analysis copy and JSON exports are research
artifacts; they are not executed as a client plugin.


## 2026-10-15 设备身份专项

设备来源到输出共享区的研究结果见 [设备身份中文报告](device_identity/REPORT.zh-CN.md)、[构建与复现说明](device_identity/README.md) 和 [证据索引](device_identity/evidence/INDEX.md)。新研究数据库为 `device_identity/prism-device-identity.i64`，既有数据库保持原 SHA256。

本专项确认：Widevine `deviceUniqueId` 大写 hex 后加固定盐 SHA256，失败回退至 boot_id；task 17 的 ClientPropsChecker 构造 event 19，运行时 HMAC 密钥认证，再以 AES-256-GCM 封装并写入 type 5 输出共享 ring。C++17 宿主/Android arm64 均已构建，最终专项检查 117 项 PASS。Android 未真机运行，完整握手、多槽 writer 的常量处理、宿主发送与服务端设备封禁规则仍未闭合；详见专项报告中的边界。交付包为 `device_identity/prism-device-identity-deliverables.zip`。
