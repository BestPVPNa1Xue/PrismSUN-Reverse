# 环境、内存完整性与输入法研究实现

详细结论：[中文报告](REPORT.zh-CN.md)。证据：[索引](evidence/INDEX.md)。这是 Android AArch64 样本的语义子集重建，不是原插件的ABI兼容替代品。

## 构建

在 PowerShell 中从 `D:/PrismSUN` 执行：

```powershell
& ./research/environment_memory/scripts/build.ps1
```

脚本默认使用 `D:/msys64/ucrt64/bin/g++.exe` 和 Android NDK `27.0.12077973`，可通过 `-HostCompiler`、`-Ndk` 参数指定路径。C++17、O2、Wall、Wextra、Werror；Android目标 `aarch64-linux-android24`。宿主JNI头通过 `-idirafter` 使用NDK的jni.h，避免用Android libc头覆盖Windows标准头。

产物：

- `build/host/prism_environment.exe`：离线ELF区段基线演示。
- `build/host/prism_environment.dll`：C++模型与JNI适配器；C++接口使用编译器ABI。
- `build/host/unit_tests.exe`、`jni_adapter_tests.exe`：宿主测试。
- `build/android-arm64/prism_environment`：Android离线演示可执行文件。
- `build/android-arm64/libprism_environment.so`：Android模型与JNI适配器。

宿主演示：

```powershell
$env:PATH='D:/msys64/ucrt64/bin;'+$env:PATH
& ./research/environment_memory/build/host/prism_environment.exe ./libprism-sun.so
```

演示只读指定文件，不扫描游戏进程。以本项目原ELF作为输入得到的是该文件的离线基线，不是四个Android系统库的运行结果。

也提供 `CMakeLists.txt`：支持普通CMake静态核心/演示/模型测试，以及Android工具链下的JNI共享库。**本轮实际执行的是PowerShell构建路径；CMake路径未另外运行。**

## 使用接口

`make_elf_baseline()` 接收标准ELF64小端AArch64字节，返回前两个带SHF_EXECINSTR标志的区段和摘要。模型额外验证魔数、架构、标准64字节区段头与文件边界；原件对异常文件的行为不承诺等价。掩码由调用方注入，默认0；它不是可信签名。

`parse_maps_text()` 只做格式解析，不还原原件的两个混淆过滤器。`compare_mappings()` 必须使用已筛选、原顺序候选列表，并提供读取回调。基线以引用传入，因为+56备用基址会跨调用保留/消费。返回 `code` 为可选值；先检查 `complete`，读取失败时没有原件返回码。`local_termination`只记录原件意图，模型不会杀死进程。

`run_environment_cycle()` 接收已取得的四库检查结果与TracerPid，只复现单轮状态规则。初始化失败用 `precheck_failed` 表示；缺失必需的库结果使 `complete=false`。线程启动、锁、休眠、诊断周期和异常展开不在此接口中。`event21_flags()` 的顺序是art/android/libc，`event24_value()` 为art标志的0/1。

`enumerate_input_methods(JavaVM*)` 使用已验证的JNI scope，在调用线程上获取环境，必要时附加，并只分离自己附加的线程。也可用 `enumerate_input_methods_from_context(JNIEnv*, jobject)` 接收借用的Context。枚举结果 `complete=false` 时不要更新 `InputMethodState`。显式异常检查和空值保护是重建实现增强，异常保持pending，不会清除。

`evaluate_input_methods()` 接收完整服务名快照，保留原序载荷，使用排序副本的CRC32检测变化，输出首次34/变化35/相同kind1。参数 `jni_environment_available=false` 仅表达环境获取失败，不应拿来代表所有JNI异常。字节接口不自动进行Unicode转换；真实输入来自JNI modified UTF-8。

## 验证与依赖

- [host-tests.json](evidence/host-tests.json)：73项宿主模型检查，其中15项比对旧原指令保存结果。
- [jni-tests.json](evidence/jni-tests.json)：8个JNI mock场景。
- [build.json](evidence/build.json)：编译器路径、flags、产物哈希和运行边界。
- [verification.json](evidence/verification.json)：样本保护、文档链接、构建产物、离线演示核对。
- [manifest.json](manifest.json)：交付源码、测试、证据和依赖哈希。

`tests/test_integrity_digest.py` / `test_ime_hash.py` 及对应JSON是上个会话的有界原指令研究记录，本轮没有重跑。`tests/saved_digest_vectors.inc` 从其结果生成，构建时直接编译，不需要Unicorn或REA。

本目录构建依赖相邻 `research/src/observed_models.*`、`class_probe_model.*` 与 `research/accessibility/src/accessibility_env.*`。不要仅拷贝本目录而遗漏这些依赖。Android只完成交叉编译，未部署、未在设备运行。原始样本与旧数据库不写入；本轮只保存了专项研究数据库。
