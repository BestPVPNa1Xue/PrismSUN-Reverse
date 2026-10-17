# ACE 无障碍监测链专项逆向报告

日期：2026-10-11。样本：`D:\PrismSUN\libprism-sun.so`，Android AArch64 ELF。

SHA-256：`92e7d4adda7e222aa9dce389009a186adabb2602b80d618d417e0f6d509adaf4`。

## 结论

本链的本地逻辑是：**枚举当前已启用无障碍服务的 ID，形成字符串数组；用排序后的 ID 集合计算 32 位指纹；首次生成事件 25，变化生成事件 33，相同指纹返回空结果。** 它不是只查询某个应用显示名称，也不是在该函数中直接返回“作弊/正常”。

KeyMapper 是本次调查的用户线索。在已恢复的 JNI 枚举、名称处理、CRC 和事件选择路径内，没有发现 KeyMapper 专用字符串匹配、包名过滤、黑名单查表或针对它的分支。KeyMapper 若有已启用服务，会与其他已启用服务一样进入这条采集链。仅凭这些本地证据，不能断言服务端如何使用其 ID，也不能断言实际处罚是否由它触发。

交付代码是可编译的语义重建，包含 JNI 枚举适配器、精确哈希、事件状态机和集成接口。它不是原始开发源码，也不是原 SO 的 ABI 兼容替代品。源码与原件的异常保护差异在下文单独列明。

## 范围与证据方法

只分析无障碍任务及其直接依赖。复用上一轮 ELF 清单、字符串解码和研究数据库；本次另复制为 `prism-accessibility.i64`，所有新增函数定义写入此副本。

实际使用 REA 6.4.0 的 IDA provider 对原始 ELF 执行 `open_binary → analyze_function × 3 → close_binary`。完整 Evidence 保存于 [evidence/rea](evidence/rea/summary.json)：

| 函数 | REA Evidence ID | 实际返回与限制 |
|---|---|---|
| 消费者 `0x6cf0c8` | `ev_aace96ad3c638ac34be5c4961abded8421efde9bdd297cb29c809a8752fc34e9` | 5,929 字符伪代码、385 条汇编记录 |
| 枚举器 `0x31b73c` | `ev_c564a1a4b27598863f44a7ebd0d76ca5e493120273babd5f29e75e2c50340756` | 16,777 字符伪代码、1,030 条汇编记录 |
| 指纹 `0x6d4374` | `ev_1d3c25b5c79d1fd797eed346de487b7afefddf14dc86c7b8b03904f128e9c20f` | 自动识别仅 13 条指令，伪代码含 JUMPOUT，不能据此代表完整函数 |

REA headless 建立临时数据库，不继承旧 i64 的手工定义。对于缺失边界，以原 ELF 的 `.eh_frame` FDE、Capstone 原字节反汇编和有界 Unicorn 执行为依据补足。IDA `auto_analysis_ready=false`，没有宣称整个数据库分析已完成。反编译类型、参数及寄存器流仅作为线索，关键结论经原指令交叉确认。

## 端到端数据链

```text
AccessibilityServiceChecker 的采集回调
  → 0x6cf0c8：读取单例的首次标志，创建结果数组
  → 0x306df0：取得当前线程 JNIEnv（必要时附加到 JavaVM）
  → 0x31b73c：枚举已启用服务的 getId()
  → 按原顺序创建 cJSON 字符串数组
  → 复制名称 vector
  → 0x6d4374：按无符号字节排序 → 每项加 NUL → CRC32 → 字节交换
  → 比较/更新单例 +552 的指纹与 +556 的首次标志
  → 0x634e84：事件 25 或 33；相同则 0x6d49a8 返回空结果
```

任务名、虚表、构造与注册证据见 [调度边界笔记](notes/scheduling.md)。`.init_array` 的 `0x6b6f3c` 经 `0x6b6a78 → 0x6b7340` 将工厂以编号 **38** 交给通用注册表 `0x601c58`。原指令合成注册表验证确认只注册一次，工厂最终生成 `AccessibilityServiceChecker`。虚表 `0x793de8` 的 `+0x40` 指向本消费者；`+0x48` 回调转调该入口；`+0x50` 查询共享首次标志。几个元数据方法返回的数字不能在缺少调度器调用点和单位证据时解释成秒数。

## JNI 环境与枚举

获取环境使用 JNI 1.6：`GetEnv(..., 0x10006)`，只有 `JNI_EDETACHED (-2)` 才调用 `AttachCurrentThread`。新附加成功时记录作用域所有权，离开时才 `DetachCurrentThread`；已经附加的线程不被本作用域分离。详见 [JNI 分析笔记](notes/accessibility-jni.md)。

枚举过程中的类、方法与参数均已恢复：

```text
ActivityThread.currentActivityThread().getApplication()
  → Context.ACCESSIBILITY_SERVICE 静态字段
  → Context.getSystemService(String)
  → AccessibilityManager.getEnabledAccessibilityServiceList(-1)
  → java.util.List.size() / get(i)
  → AccessibilityServiceInfo.getId()
  → GetStringUTFChars → std::string → ReleaseStringUTFChars
```

- `-1` 是 `FEEDBACK_ALL_MASK`，覆盖所有反馈类型；API 返回已启用服务。
- 输出是 ID，不是应用 label、服务显示名称、安装列表或用户交互日志。
- `size()` 只调用一次，循环采用有符号 `i < count`。
- null list、零或负 count 产生空 vector；每个 null ID / null UTF chars 形成一个空字符串。
- 保留列表顺序、重复项与空字符串。编码为 JNI modified UTF-8，不进行大小写折叠或 Unicode 归一化。
- 正常路径释放临时 Java 引用与 UTF chars。原包装没有显式检查/清除 Java pending exception，不能把 C++ unwind 清理误认为 Java 异常处理。
- `0x31b73c` 通过 AArch64 X8 返回 vector。X0 中的清理返回值不是检测分数。

先前缺失的短 token `get\0` 与 `()I\0` 已用原指令前缀复演和 XOR 数据流补齐，见 [jni-short-strings.json](evidence/jni-short-strings.json)。11 个 JNI 表槽位与 NDK `jni.h` 的 `offsetof` 断言一致。

## 精确指纹算法

```text
sorted = unsigned_byte_lexicographic_sort(copy(ids))
bytes  = concat(each_id_bytes + 00)
crc    = CRC32_IEEE(bytes)
hash   = little_endian_u32(big_endian_bytes(crc))
       = bswap32(crc)
```

CRC 反射多项式 `0xedb88320`，初始值 `0xffffffff`，最终异或 `0xffffffff`。原件调用 Botan 的 `CRC32`，摘要长度本来就是 4 字节；没有从 SHA 等较长摘要中截取，也没有加盐。原件实际解码的全部 256 个查表项已与多项式生成结果逐项核对。

每个 ID 的完整 `data()/size()` 参与哈希，然后加一个零字节。无元素数、无长度前缀、无 JSON 引号、无逗号。排序不去重，按无符号字节词典序，短前缀在前。

| 输入（测试字节） | 原件指纹 |
|---|---:|
| `[]` | `0x00000000` |
| `[""]` | `0x8def02d2` |
| `["", ""]` | `0xff12d941` |
| `["a"]` | `0x19483f3d` |
| `["a", "b"]` 或 `["b", "a"]` | `0x5f4615f5` |
| `["a", "a", "b"]` | `0x1fe43ba6` |
| `["z", "a"]` | `0x06de0e77` |

因此，服务顺序变化会被抑制，增删、重复数量、ID 字节变化通常会产生新指纹。32 位 CRC 相同不能证明数组严格相同。嵌入原始 NUL 的合成 std::string 输入还可能出现串联边界歧义；Android JNI 会把 Java U+0000 编成 `c0 80`，不能把合成原始 NUL 用例当作真实服务 ID 的已观察行为。

完整函数地图、排序、Botan 虚表与差分证据见 [hash.md](notes/hash.md)。

## 状态机、载荷与错误结果

共享单例由 `0x3b8c40` 返回：

| 偏移 | 宽度 | 意义 |
|---|---|---|
| `+552` / `+0x228` | 32 位 | 上次采集指纹 |
| `+556` / `+0x22c` | 1 字节低位 | 是否已执行首次成功采集 |

原单例构造器在 `0x3d799c..0x3d79b0` 分别对这两个字段调用零值构造；已单独执行原字段构造器验证写入 32 位 0 和单字节 0，并验证相邻字节未被改写，见 `evidence/state-init.json`。没有为此展开其他状态字段的检测逻辑。

首次标志在采集前读取。包装器传入顺序参数 5，原路径落入 ARM64 acquire/release 原子指令；重建采用 `std::memory_order_seq_cst` 对应这种编译映射。未把两个原子字段发明成一个加锁事务，也没有声称验证过多线程调度和竞争。

| 条件 | 状态更新 | 输出 |
|---|---|---|
| JNIEnv 获取失败 | 两字段不变 | `kind=2, type=0, payload=null, error=0xBBA` |
| 未初始化，采集成功（包含空列表） | 先置首次标志，再写新指纹 | `kind=0, type=25, payload=原顺序ID数组` |
| 已初始化，指纹不同 | 只写新指纹 | `kind=0, type=33, payload=原顺序ID数组` |
| 已初始化，指纹相同 | 不变 | `kind=1, type=0, payload=null, error=0` |

重要边界：首次没有任何服务，也会生成 `25 / []`；从有服务变成空列表生成 `33 / []`；JNI 获取失败不是空服务列表。未变化并不是跳过采集：仍会枚举、构造临时数组并计算指纹，之后才销毁临时载荷并返回空结果。

载荷构造为 `0x2a8358`（cJSON array/type 32）→ `0x2a829c`（string/type 16）→ `0x2a7fec/0x2a8048`（添加子项）。数组保留原返回顺序；哈希排序发生在副本中。`CreateString` 接收 `c_str()`，理论上的原始 NUL 会截断 JSON 字符串，而 hash 使用完整 size；相关边界已纳入合成差分。

结果对象的已验证字段：

| 偏移 | 字段 | 已验证含义 |
|---|---|---|
| `+0` | u32 kind | 0=事件，1=空结果，2=错误 |
| `+4` | u8 type | 25 / 33，其他上述结果为 0 |
| `+8` | 64 位指针 | cJSON 载荷所有权 |
| `+16` | u32 code | 正常/空为 0，环境失败为 0xBBA |

原件 `0x634e84`、`0x635514`、`0x6d49a8`、`0x6b00fc` 的实际构造指令均在本次消费者差分中执行。再次纠正反编译误差：`0x6b0348` 从保存 W0 的位置读取错误码，再写 `output+16`；伪代码把它误识别成了 X1 的一部分。`0x2b2208(0xBBA)` 是该值的包装返回，不改变数值。

## 可编译重建与使用

| 文件 | 作用 |
|---|---|
| [src/accessibility_core.hpp](src/accessibility_core.hpp)、[.cpp](src/accessibility_core.cpp) | 精确排序/CRC、三类结果、25/33 状态机、测试 C ABI |
| [src/accessibility_jni.hpp](src/accessibility_jni.hpp)、[.cpp](src/accessibility_jni.cpp) | 已恢复的 Android API 枚举链与局部引用管理 |
| [src/accessibility_env.hpp](src/accessibility_env.hpp)、[.cpp](src/accessibility_env.cpp) | GetEnv/Attach/Detach 的线程作用域 |
| [src/accessibility_monitor.hpp](src/accessibility_monitor.hpp)、[.cpp](src/accessibility_monitor.cpp) | 将 JNI 完整快照交给状态机的集成入口 |
| [src/accessibility_demo.cpp](src/accessibility_demo.cpp) | 宿主输入同一列表两次，演示首次与抑制 |
| [CMakeLists.txt](CMakeLists.txt)、[scripts/build.ps1](scripts/build.ps1) | C++17 宿主与 Android ARM64 构建 |

调用方式、构建和产物路径见 [README.zh-CN.md](README.zh-CN.md)。所有源码在当前工作区可直接编译，不需要连接游戏或修改原件。

与原件的明确差异：

1. JNI 适配器增加逐阶段异常/必要对象检查，不清除 Java 异常；`complete=false` 不被送入状态机作为完整列表。这是重建的健壮性设计，原样本没有这些检查。
2. UTF chars 使用 RAII，改善 C++ 分配异常时的释放。保留了原正常路径的输入、输出和顺序契约。
3. C++ STL 布局、cJSON 内存对象、混淆状态机、函数入口自检和栈保护不做 ABI 复刻。提供紧凑 JSON 文本仅用于查看结果，不声称是原传输序列化。
4. 正常可分配条件已差分；未模拟 OOM、损坏容器、C++ unwinder、Java VM 异常后的所有后果。原 cJSON 创建/追加返回值未在消费者中逐项检查，重建 STL 分配失败会抛异常，不能宣称这些资源失败分支等价。
5. 需要由调用者按真实线程生命周期提供 JNI 环境或 JavaVM；未自行发明后台轮询周期、远程地址或处罚策略。

## 验证结果

- **原哈希 42/42 PASS**：原件排序、CRC 工厂/update/final、结果提取全执行，独立参考为 `zlib.crc32 + bswap32`。含 129 项排序、22/23 字节 libc++ 字符串边界、16 字节 CRC 分块边界、固定随机数据、空值/重复/MUTF-8 字节等。
- **消费者 180/180 PASS**：执行原始 `0x6cf0c8`，包含实际 cJSON、vector 拷贝/排序、CRC、原子状态包装和结果构造；只模拟 singleton 定位、JNI 服务 ID 输入与获取作用域、诊断文字及 libc/TLS 宿主边界。对比 kind/type/code/payload 字节顺序、两字段状态和输出保护区。
- **C++ 最终产物回放 PASS**：75 个独立指纹检查、全部 42 个原哈希记录、180 个原消费者结果与最终 DLL 一致。见 [core-final-replay.json](evidence/core-final-replay.json)。
- **JNI 适配器 8/8 PASS**，11 个 NDK JNI 表槽位编译期断言通过。测试检查完整 API 签名、mask、size 调用次数、顺序/重复、空值、pending exception 与引用释放。它验证重建适配器，不冒充真实 Android 设备测试。
- **JNI 环境作用域 6/6 原指令、6/6 C++ PASS**：null VM、已附加、版本错误、附加成功、附加失败、其他 GetEnv 错误；3 个 JavaVM 表槽位编译期断言通过。见 [原指令验证](evidence/jni-env-scope-emulation.json) 与 [构建验证](evidence/jni-env-build-verification.json)。
- **任务注册/工厂原指令验证 PASS**：实际执行专属初始化和构造链，仅模拟通用 registry getter/insert，确认编号 38、工厂虚表及最终 checker 虚表，见 [注册证据](evidence/hash-upstream-scheduling-emulation.json)。
- 宿主 DLL/EXE、Android ARM64/API24 共享库编译通过，开启 `-std=c++17 -O2 -Wall -Wextra -Werror`。构建工具链与源码/产物哈希见 [build.json](evidence/build.json)。初始宿主 clang 与 GCC 静态库有重复 RTTI section 告警，最终统一为该 MSYS2 环境的 g++，最终核心回放覆盖最终产物。

原哈希首次 129 项排序碰到 10 秒仿真预算，仅对失败项增加有界预算后复验通过；初始记录保留。没有把超时写成算法错误，也没有隐藏失败记录。完整消费者与哈希仿真不运行 Android 程序，不转发系统调用或未知 import。

## 尚未由本次证据证明的内容

- 实际 Android 设备的服务列表、hidden API 策略、Application 初始化时机及真实 Java 异常表现。
- 通用调度器的确切运行周期/触发时刻与并发行为；数值元数据未擅自附加单位。
- 事件 25/33 后续是否、何时、以何种协议传输，以及任何服务端规则与处罚。当前证据终点是本地结果对象及其任务调用接口。
- KeyMapper 专用判定。不能把“可被通用采集包含”与“已证明专用作弊规则”混为一谈。

## BEFORE / AFTER / ROLLBACK

- **BEFORE**：已知无障碍枚举和事件 25/33，但 `getId`、mask、错误分支、哈希算法/端序/排序及对象布局未完整核实。
- **AFTER**：上述本地数据链均有原指令或 JNI 表/字符串证据；语义实现可编译并经过差分。所有新增证据和报告保存在本专项目录。
- **ROLLBACK**：没有修改原 SO、原 i64、旧研究 i64、Android 设备或游戏进程。关闭新的研究数据库后即可归档整个本专项目录；无需恢复目标程序。原件保护最终校验见 `evidence/final-verification.json`。REA 的安装回滚单独记录在 `research/tooling/rea/README.zh-CN.md`。
