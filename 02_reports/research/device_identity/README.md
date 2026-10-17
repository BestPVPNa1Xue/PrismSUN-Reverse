> 归档阅读副本：只调整文件超链接；原文、代码块中的历史路径与结论保持原样。[逐字节原始文件](../../../03_evidence/original_documents/research/device_identity/README.md)。历史失效链接转到文件索引，原目标见 `00_guide/report-link-audit.json`。

# PrismSUN 设备身份专项

本目录提供设备 ID 到事件 19、HMAC、AES-GCM 和输出共享 ring 的证据及可编译 C++17 重建。源码已在 Windows 和 Android arm64 交叉编译；宿主验证有 117 项 PASS。Android 未真机运行，宿主网络发送与服务端封禁规则仍未知。完整结论和工程差异见 [中文报告](REPORT.zh-CN.md)，证据导航见 [证据索引](evidence/INDEX.md)。

## 文件

- `src/`：自包含密码算法、身份/事件模型和 Android JNI/MediaDrm adapter。
- `tests/`：C++ unit 和 Python 独立 oracle/保存结果对照。
- `scripts/`：构建、原 ELF 指令实验、静态采集和交付清单生成。
- `evidence/`：原汇编、仿真结果、REA dossier、验证和完整性记录。
- `decompiled/`：按地址保存的 IDA 伪代码；混淆/反编译错误不直接作为行为结论。
- `prism-device-identity.i64`：单独保存的研究数据库，含 17 个函数命名和 5 处注释。
- `build/host/`：`prism_identity.exe`、`unit_tests.exe`。
- `build/android-arm64/`：`prism_identity`、`libprism_identity.so`。

## 已验证的构建方式

在 PowerShell 执行，脚本按顺序编译，不创建代理或并行构建任务：

```powershell
Set-Location 'D:\PrismSUN'
& '.\research\device_identity\scripts\build.ps1'
```

默认工具路径是 `D:\msys64\ucrt64\bin\g++.exe` 和 NDK `C:\Users\ASUS\AppData\Local\Android\Sdk\ndk\27.0.12077973`，可通过参数指定：

```powershell
& '.\research\device_identity\scripts\build.ps1' `
  -HostCompiler 'D:\msys64\ucrt64\bin\g++.exe' `
  -Ndk 'C:\Users\ASUS\AppData\Local\Android\Sdk\ndk\27.0.12077973'
```

编译 C++ 本身不需要 Python、IDA、REA、原 SO 或额外密码库。Android 共享库需要 NDK 的 JNI/MediaDrm 头文件和 dl。Windows executable 使用当前 MinGW 运行库 DLL，运行时需将编译器 bin 加入 PATH；压缩包不捆绑这些系统工具 DLL。`CMakeLists.txt` 也提供 GCC/Clang 的 shared library 与 demo target，但本次验证使用的是上述 PowerShell 构建脚本，不声称已验证所有 CMake/编译器组合。

## 合成演示

```powershell
$env:PATH='D:\msys64\ucrt64\bin;'+$env:PATH
& 'D:\PrismSUN\research\device_identity\build\host\prism_identity.exe' demo
& 'D:\PrismSUN\research\device_identity\build\host\unit_tests.exe'
```

demo 使用合成 Widevine 字节 `0001FEFF`、字符串 `CHALLENGE`、`TEST_KEY` 和合成应用字段，输出事件和 packet。它不采集 Windows 的真实设备信息，也不连接服务器。

其他 CLI 命令包括 `sha HEX`、`hmac KEYHEX MSGHEX`、`drm HEX`、`boot TEXTHEX`、`salted TEXTHEX`、`packet MSGHEX KEYHEX GENERATION SEQUENCE NIBBLE`、`activities NAME...`、`certificate APKHEX` 和 `ring TYPE HEAD TAIL HEX OUTPUT`。字节/文本参数用 hex 传入，可表示 NUL；输出 hash/packet 使用大写 hex。`event` 命令用于固定 TEST_KEY/合成应用字段的差分 fixture，完整参数格式见 `src/main.cpp`。

## C++ API 和 Android 接入

`identity.hpp` 的核心接口是 `choose_identity`、`activity_info`、`Session::install`、`client_properties`、`encode_result` 和 `Ring::write`。例如：

```cpp
#include "identity.hpp"

prism::Session session;
session.install(prism::Bytes(32, 0x42), prism::bytes("TEST_KEY"), 1);
auto id = prism::choose_identity(prism::unhex("0001FEFF"), "TEST_BOOT_ID");
prism::AppInfo app{"APP_PACKAGE", "TEST_DIGEST", {"test.package", true}};
auto result = prism::client_properties({std::string("CHALLENGE")}, id, app, session);
auto record = prism::encode_result(result, session, 10);
prism::Ring ring;
if (record) ring.write(*record);
```

Android C++ 调用者可以包含 `android_adapter.hpp`，传入当前线程已有效的 `JNIEnv*` 和 application context，调用 `collect_android_properties`。适配层不创建/attach 线程。`libprism_identity.so` 是研究用 C++ API，未实现原 PrismSUN 插件 ABI、宿主 Java native 注册、握手协议或服务器客户端。随机 nibble 由调用者提供。重建的资源管理和错误映射差异见报告。

## 验证与原件实验的复现边界

```powershell
& 'D:\Python 314\python.exe' `
  'D:\PrismSUN\research\device_identity\tests\verify.py'
```

该脚本将 C++ 输出与独立 Python SHA/HMAC/AESGCM、保存的原指令结果比较，并运行 unit_tests。成功时写 `evidence/verification.json`，当前结果为 117 项 PASS。它不重新执行所有原件实验。脚本的导入链仍依赖 `cryptography`、`unicorn`、`pyelftools` 和既有 harness 文件；当前研究树中已具备这些依赖。它默认使用本机 MinGW bin 路径，其他环境需要调整。

重新生成 `scripts/*_original.py` 的结果，需要原样本 SHA-256 匹配、保持 `D:\PrismSUN` 的研究树层级，以及：

```text
research/accessibility/scripts/hash_original.py
research/scripts/bounded_arm64.py
libprism-sun.so
```

`static_probe.py` 还依赖既有 ELF FDE 元数据和 Capstone；`ida_capture.py` 依赖活动 IDA MCP endpoint，默认的历史端口 1247 不能当作当前服务地址，需要显式传入 `--endpoint`。不应对完整性已通过且没有变更的实验盲目重跑。压缩包包含专项脚本和保存的结果，但不包含原 SO、这些外部 harness 或 IDB；**可独立编译源码，不可独立重跑所有原件仿真**。

多槽原 writer 的成功异常没有闭合；最终 verifier 排除 4089/65408 字节的原多槽成功场景。C++ ring 使用 4088 字节的工程分片，并非跨进程原子队列。117 项检查也包含保存结果的一致性断言，不能解释为全模块/真机/服务端的 117 次端到端差分。

## 完整性和交付

`evidence/before.json` 与 `after.json` 核对四个原文件；`manifest.json` 给出专项文件和研究 IDB 哈希。`scripts/finalize_artifacts.py` 在本研究树中生成清单和交付 zip，并检查 zip 内容：

```powershell
& 'D:\Python 314\python.exe' `
  'D:\PrismSUN\research\device_identity\scripts\finalize_artifacts.py'
```

交付包为 `prism-device-identity-deliverables.zip`，其校验记录是 `evidence/delivery.json`。原件、大 IDB、IDA sidecar、缓存和历史压缩包均不进入新包。manifest/delivery 通过明确的自引用排除避免循环哈希；原 SHA 不变不代表新研究 IDB 无修改。
