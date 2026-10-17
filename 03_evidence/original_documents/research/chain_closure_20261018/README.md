# Prism四链C++重建

先读[报告](REPORT.zh-CN.md)和[静态地址笔记](CHAIN_NOTES.zh-CN.md)。Android APK构建计划仍由用户下一步制定；此目录只提供C++源码、编译验证和研究证据。

目录：

```text
src/       纯语义核心、JNI适配、Android ARM64采集器
tests/     宿主边界测试、JNI/VM表mock
scripts/   build.ps1、证据查看、静态字符串解码、verify.py
build/host/             unit_tests.exe、jni_tests.exe
build/android-arm64/    libprism_chains.so、unit_tests、jni_tests
evidence/               IDA导出、测试/构建记录、保护文件哈希
prism-chain-closure.i64 本轮独立研究数据库
prism-chain-closure.snapshot.i64 已保存数据库的交付快照，未被IDA打开
```

在PowerShell执行（默认依赖路径已在当前机器核验）：

```powershell
Set-Location D:\PrismSUN
& .\research\chain_closure_20261018\scripts\build.ps1
& 'D:\Python 314\python.exe' .\research\chain_closure_20261018\scripts\verify.py
```

依赖：MinGW UCRT g++、Android NDK 27.0.12077973、C++17；Android目标aarch64-linux-android24。脚本参数`-HostCompiler`、`-Ndk`可覆盖路径。构建脚本运行Windows测试，编译Android产物，不执行Android代码。

核心入口见[detection_chains.hpp](src/detection_chains.hpp)。Android真实采集见[android_collectors.hpp](src/android_collectors.hpp)，JNI见[classes_jni.hpp](src/classes_jni.hpp)。`inspect_seccomp()`默认不主动安装handler；需要主动probe但没运行时`complete=false`。所有结果都应先检查complete，再使用原件判定字段。

四库使用`compare_library`与既有`make_elf_baseline`/`run_environment_cycle`组合；调用方提供文件基线、可验证的MemoryReader及前置门控结果。event22使用typed `JsonValue`，传入真实JavaVM；配置字符串不做点/斜线转换。event20只提供已确定的计数消费边界，不是完整raw reader。

本轮验证：112项核心+10项JNI检查通过；Android只交叉编译，原SO未运行。保护文件4/5匹配，历史environment-memory研究IDB哈希变化，完整性验收单独标为失败。原因线索与恢复边界见报告，详细记录见[verification.json](evidence/verification.json)。
