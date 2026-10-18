# Prism old checks

C++17 semantic reconstruction of PSR_20250811.531a9c4: Xposed/Epic, seven paths, maps event20 and status debug checks.

Build and run host tests, then cross-compile the Android ARM64/API24 shared library:

```powershell
./scripts/build.ps1 -HostCompiler D:/msys64/ucrt64/bin/g++.exe -Ndk C:/path/to/ndk
```

Outputs are local to `build/` and ignored by Git. No dependencies on other research modules. The JNI header comes from the selected Android NDK. Build results do not imply execution on Android.

See [the report](../../../02_reports/research/prism_old_checks_20261018/REPORT.zh-CN.md) for original addresses, validated behavior, and explicit ART/baseline/error boundaries. `inspect_loader` changes the identified callback fields; callers choose the environment and supply loader objects. `accept_token(0)` resets the scan cache. The original termination backend and background scheduler are outside this module.
