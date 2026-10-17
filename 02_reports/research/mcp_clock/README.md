> 归档阅读副本：只调整文件超链接；原文、代码块中的历史路径与结论保持原样。[逐字节原始文件](../../../03_evidence/original_documents/research/mcp_clock/README.md)。历史失效链接转到文件索引，原目标见 `00_guide/report-link-audit.json`。

# PrismSUN MCP 文件链与时钟链

2026-10-17，接续会话 `01a14573-7a3b-7463-9e36-0a68db497e5b`。本轮仅通过 IDA Pro MCP 获取逆向证据，未调用 REA、未使用子代理、未继续上报链。

两条指定链已整理为可独立编译的 C++17 模块。完整解释见 [REPORT.zh-CN.md](REPORT.zh-CN.md)，函数与证据对照见 [evidence/INDEX.md](evidence/INDEX.md)。这是去混淆后的语义重建；不是原 SO 的 ABI 替换件。

## 源码与产物

| 模块 | 源码 | 已构建 Android 产物 |
| --- | --- | --- |
| 两遍 fd 扫描、MCPK 文本解析、事件 32 数组 | `src/mcp_chain.hpp`、`src/mcp_chain.cpp` | `build/android-arm64/libprism_mcp_chain.so` |
| 时钟选择、32 字节附加输入、HMAC_DRBG 消费 | `src/clock_chain.hpp`、`src/clock_chain.cpp`、`src/crypto.cpp`、`src/sha_constants.inc` | `build/android-arm64/libprism_clock_chain.so` |
| 演示和测试 | `src/main.cpp`、`tests/unit_tests.cpp`、`tests/oracle_tests.py` | `build/android-arm64/prism_mcp_clock`、`build/android-arm64/unit_tests` |

Windows 程序：`build/host/prism_mcp_clock.exe`、`build/host/unit_tests.exe`。

## 构建与使用

从 `D:\PrismSUN` 执行：

```powershell
& .\research\mcp_clock\scripts\build.ps1
& 'D:\Python 314\python.exe' .\research\mcp_clock\tests\oracle_tests.py
$env:PATH='D:\msys64\ucrt64\bin;'+$env:PATH
& .\research\mcp_clock\build\host\prism_mcp_clock.exe clock
```

构建脚本使用现有 MinGW g++ 和 NDK 27，启用 `-std=c++17 -O2 -Wall -Wextra -Werror`。脚本记录编译器、参数、测试和产物哈希到 `evidence/build.json`。保留了 `CMakeLists.txt` 供常规工具链使用，本轮实际验证的是 PowerShell 构建入口。

Linux/Android 中运行 `prism_mcp_clock mcp` 可枚举**运行该程序的进程**的 fd；作为库嵌入另一个进程时，应由调用者传入该进程 PID。独立命令不会自动获得原游戏进程的 fd。

```cpp
#include "mcp_chain.hpp"
#include "clock_chain.hpp"

prism::clockchain::NativeServices services;
prism::mcp::NativeFiles files;
auto scan = prism::mcp::collect(files, services.pid());
auto array_json = prism::mcp::event32_payload(scan);
// array_json 有值时，结果语义为 kind=0 / event=32 / payload=该数组。

prism::clockchain::HmacDrbg rng(services); // SHA-512，1024 次间隔
auto output = prism::clockchain::auto_seeded_generate(rng, services, 32);
```

Windows 不提供相同的 `/proc/<pid>/fd`；`mcp` 命令会明确报不支持，单元测试使用 `FileOps` 可控夹具。Windows `clock` 用 steady_clock 和 BCrypt 作为宿主适配；Linux/Android 使用原链对应的 clock_gettime/getpid/arc4random_buf。

## 已验证范围

- 宿主 46 项检查通过：目录/筛选/文本/事件、时钟失败顺序、附加输入、小端布局、RNG 分派、播种计数与 PID 变化。
- 独立 Python hashlib/hmac 对照 98/98：SHA-256、SHA-512、两种 HMAC、DRBG 附加输入及 65536 字节分块。
- Android ARM64/API 24 的 CLI、测试程序、两份 SO 交叉编译成功；未真机执行。
- 本轮没有执行原始 ELF，也没有把 C++/Python 对照称作原件差分测试。

原件忽略若干 read/lseek 返回值。读取不足而依赖未初始化栈时，模型返回 `IndeterminateStack`，整批 `event32_payload` 返回 nullopt；不会虚构稳定结果。EOF 发生在已读到非零字节之后时，模型保留原件“重复上一字节直到 64 字节”的行为。

IDA 副本：`prism-mcp-clock.i64`；最终哈希清单：`manifest.json`；验收：`evidence/verification.json`。原始样本、旧数据库和旧研究产物保持原样。
