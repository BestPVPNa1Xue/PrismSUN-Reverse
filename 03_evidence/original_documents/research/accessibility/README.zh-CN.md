# 无障碍监测链可编译重建

从 `libprism-sun.so` 恢复的 Android 无障碍服务采集与变化记录链。完整结论与证据边界见 [REPORT.zh-CN.md](REPORT.zh-CN.md)。只覆盖此任务，不包含其他反作弊探针。

## 构建

当前 Windows 环境：

```powershell
& 'D:\PrismSUN\research\accessibility\scripts\build.ps1'
```

脚本使用 MSYS2 UCRT64 g++ 与 NDK r27 clang，C++17、Android `aarch64-linux-android24`，仅对当前 PowerShell 进程设置运行库搜索路径，不改系统 PATH。

产物：

- `build/host/accessibility_core.dll`：纯状态机/指纹测试 ABI。
- `build/host/accessibility_demo.exe`：输入相同列表两次，输出事件 25 然后空结果。
- `build/android-arm64/libaccessibility_reconstruction.so`：状态机、JNI 枚举与集成接口。

```powershell
$env:PATH = 'D:\msys64\ucrt64\bin;' + $env:PATH
& 'D:\PrismSUN\research\accessibility\build\host\accessibility_demo.exe' 'TARGET/.ServiceB' 'TARGET/.ServiceA'
```

已验证示例输出：

```text
kind=0 event=25 hash=0x12655b6d payload=["TARGET/.ServiceB","TARGET/.ServiceA"]
kind=1 event=0 hash=0x12655b6d payload=null
```

提供了 `CMakeLists.txt` 方便其他环境集成；当前实际验收走 PowerShell 构建脚本。Android CMake 可使用 NDK 的 `android.toolchain.cmake`、`ANDROID_ABI=arm64-v8a`、`ANDROID_PLATFORM=android-24`。

## Android 集成

在已有 native 工程中编译 `src` 下的实现；State 的生存期应覆盖多次采集。调用线程必须具有有效 JNI 环境：

```cpp
#include "accessibility_monitor.hpp"

prism::accessibility::State state;

void collect(JNIEnv* env) {
    auto observation = prism::accessibility::observe(state, env);
    if (!observation.result) {
        // Defensive adapter stopped: inspect enumeration.diagnostics;
        // Java exceptions remain pending. No partial snapshot is committed.
        return;
    }
    const auto& result = *observation.result;
    // kind 0: event_type 25 or 33 and payload IDs
    // kind 1: unchanged
    // kind 2: JNI environment unavailable, error_code 0xbba
    auto text = prism::accessibility::payload_json(result);
    // Consume locally in your application. No network transport is provided.
}
```

`observe_from_context` 接收借用的 Context，便于测试环境明确提供 Context；原样本自身使用 `ActivityThread.currentActivityThread().getApplication()`。

需要从 native 线程获取环境时，调用 `observe_vm(state, vm)`：它使用恢复的 `ScopedJniEnvironment`，JNI 1.6 `GetEnv`，仅对 `JNI_EDETACHED` 附加，并在枚举后、计算结果前释放自身拥有的线程附加。传入 JavaVM 的生命周期由调用方保证；不要跨线程保存 JNIEnv。

JNI 字符串保留 modified UTF-8 字节。`payload_json` 仅表示可查看的载荷，不是恢复出的网络报文。接口遵循语义，不承诺兼容原 STL/cJSON ABI。

## 验证与复现

快速验证最终 C++ 与已经保存的原件观察结果（不重跑 ARM64 仿真）：

```powershell
& 'D:\Python 314\python.exe' 'D:\PrismSUN\research\accessibility\tests\test_core.py' --replay
```

需要重新运行全部原指令差分时：

```powershell
& 'D:\Python 314\python.exe' 'D:\PrismSUN\research\accessibility\tests\test_hash.py'
& 'D:\Python 314\python.exe' 'D:\PrismSUN\research\accessibility\tests\test_core.py'
& 'D:\PrismSUN\research\accessibility\scripts\jni-build.ps1'
& 'D:\PrismSUN\research\accessibility\scripts\jni-env-build.ps1'
& 'D:\Python 314\python.exe' 'D:\PrismSUN\research\accessibility\scripts\jni-env-scope-emulation.py'
```

Python 依赖为已有 `unicorn`、`pyelftools`、`capstone`；脚本复用上层 `research/scripts/bounded_arm64.py` 和原始 ELF。需要保留工作区布局。测试最多执行到预设指令/时间边界；未知 import/系统调用不会转发到操作系统。

REA 分析完整记录：`evidence/rea/`。本次批处理入口：`D:\PrismSUN\tools\rea\accessibility-batch.mjs`，使用已安装本地 npm/IDA provider。研究副本：`prism-accessibility.i64`。原数据库不被覆盖。

## 文件索引

- `src/`：可编译 C++ 源码和接口。
- `tests/`：原哈希差分、编译核心差分、JNI 模拟测试。
- `scripts/`：构建、原指令 fixture、专项证据采集。
- `notes/accessibility-jni.md`：JNI 生产者、方法签名、表偏移、异常与生命周期。
- `notes/hash.md`：排序、CRC、端序、字节流和原件测试。
- `notes/scheduling.md`：checker 身份、虚表、注册和调度边界。
- `evidence/core-differential.json`：180 个原指令消费者场景。
- `evidence/core-final-replay.json`：最终 DLL 对原件记录的验证。
- `evidence/build.json`：工具链及源码/产物哈希。

实际设备部署、远程上传和服务端策略均未执行。新增源码的显式异常检查与安全退出行为是工程化增强，详见报告，不归因于原程序。
