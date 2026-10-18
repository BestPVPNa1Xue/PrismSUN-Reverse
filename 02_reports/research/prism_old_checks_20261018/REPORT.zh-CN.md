# Prism 旧版小样本：Xposed/Epic、七条路径、maps 与调试检查

研究日期：2026-10-18。仅深入这四组检查，使用 IDA Pro MCP；未调用 REA 或子代理。交付的是基于证据的 C++17 语义重建，不是厂商原始源码，也不是完整 Prism 库。

## 1. 样本与结论

目标版本 **PSR_20250811.531a9c4**，选取两个旧件中较小的 `libprism-sun-2.so`。所有地址均为解包后 ELF 的虚拟地址，image base 为 0，不是压缩文件偏移。

| 对象 | 字节数 | SHA-256 |
|---|---:|---|
| 原始旧件 | 2,232,444 | `4e8f95ba601f27465a566dae63b71948e48704b5a1bc249db7e6c67a87e3b88d` |
| 解包 ARM64 ELF | 6,574,528 | `ba9ad43bd1c80b46f87f8162f55ca18c0310d64aaaa67c62bb05b69cdecc0d0a` |

本次闭合的重点：

- Xposed/Epic 是“发现桥接类、尝试关闭 hooks、替换回调数组”的组合链，具有反射容错；不是几个框架名称的简单字符串匹配。
- 七条路径以直接 `fstatat` 检查可访问性，任一成功即阳性；没有逐个判定文件类型、包签名或 root 权限。
- maps 的 event20 reader 统计大块可执行匿名映射；正常分支未见普通库路径追加。打开失败会追加确切诊断 **`8)`**。
- 调试检查返回 TracerPid 数值，另有严格的 State 字符串匹配。`6`、`-1`、描述符 `0`、末行和换行处理都与直觉可能不同，重建保留这些区别。

证据分层：**原指令验证**指原样 ARM64 指令在 Unicorn 中执行，JNI、文件读取、C++/libc 部分边界明确建模；**静态确认**指 IDA 指令、调用、参数及消费者一致；**边界保留**指尚未穷尽或原件行为未定义。本次没有 Android 真机、游戏宿主或服务端执行记录。

## 2. Xposed / Epic

### 2.1 入口、缓存与状态值

`0x411c00` 将 `0x2830d0` 的结果装入 **event24**。后者先调用 `0x215ec8`，参数达到 21 才进入其类加载器相关分支；全局 `0x654a08` 非零时直接返回，仍为零才调用 `0x25dc1c` 的栈回退检查。本次没有把参数的所有配置来源和 ART 内部类加载器枚举移植进重建库；源码接收调用者提供的 loader。

`0x25bcb4` 的顺序为：`0x24ddf0(token)` 去重 → 查找 XposedBridge → 将状态从 0 置 1 → 尝试 `disableHooks` → Epic/Xposed 回调处理成功时将小于 2 的状态置 2。`disableHooks` 的返回值在此处被忽略，因此状态 1 不代表设置成功。

| 状态 | 已证含义 |
|---:|---|
| 0 | 当前链尚未设置阳性状态 |
| 1 | 已找到 XposedBridge |
| 2 | 回调数组处理至少有一次成功写入 |
| 3 | 零状态下的栈回退命中 |

`0x24ddf0` 以原生 token 值去重，容量每次加 4，计数/容量以 XOR 常量隐藏。token 为零时转入 `0x24e198`：释放缓存、重置编码计数和指针；有缓存返回真，无缓存返回假。`0x215ec8` 的已见枚举路径结束也调用重置。源码 `accept_token` 保留此语义，状态值与扫描缓存分别存放。

### 2.2 查找已加载类与 disableHooks

`0x263228` 使用 `java/lang/VMClassLoader.findLoadedClass`，签名为 `(Ljava/lang/ClassLoader;Ljava/lang/String;)Ljava/lang/Class;`，传入 loader 和名称。其动作是查找已加载类；这区别于任意 `loadClass` 引起的新类加载。

`0x25c1bc` 获取静态字段 `disableHooks:Z`，通过 JNI `SetStaticBooleanField` 写入 true；检查并清理异常。原指令夹具确认正常返回 1、字段缺失返回 0。

### 2.3 Epic 家族顺序与动态桥接类

`0x25cdfc` 按成功短路：

1. 查 `me/weishu/epic/art2/EpicNative`，由 `0x22b0d4` 求出动态桥接类名，再交给 `0x26c370` 查类和清理回调。
2. `me/weishu/epic/art2/EpicBridge`。
3. `de/robv/android/xposed/DexposedBridge`。
4. `de/robv/android/xposed/XposedBridge`。

动态名称不是写死的字段：`0x22b0d4` 枚举 `getDeclaredMethods()`，筛选 `(modifiers & 0x108)==8`，即 static 且非 native，参数数组长度为 0，返回类型与 `java/lang/String` 精确相同。随后取得方法名，以 `()Ljava/lang/String;` 调用静态方法；异常分支会清理后继续。非空结果去掉开头的 `L`，截断到第一个 `;`，未见点号转斜杠。夹具确认 `Lexample.CallbackOwner;` 得到 `example.CallbackOwner`。

### 2.4 回调清理与字段改名容错

`0x270110` 首先查静态 `sHookedMethodCallbacks:Ljava/util/Map;`。失败后经 `0x229f44 → 0x22843c` 枚举声明字段，选取 `(modifiers & 8)==8` 且 `getType()` 与 `java/util/Map` 精确相同的字段名，然后再次取得静态字段 ID。字段声明类型为 HashMap 并不等同于 Map 的精确类型匹配。

`0x26f654` 取出此 Map 对象，运行时要求 `IsInstanceOf(java/util/HashMap)`。它调用 `isEmpty()`，若为真又调用 nonvirtual 版本，最终布尔值用于选择 `values()` 的 virtual 或 nonvirtual 调用；**不是“isEmpty 为真就直接结束”的逻辑**。随后 `values → iterator → hasNext/next` 遍历回调容器。

第一个非空 value 的类经 `0x2275cc → 0x22843c` 查找非 static 且精确类型为 `[Ljava/lang/Object;` 的声明字段。字段 ID 被缓存供后续 value 使用。它构造长度 0 的 Object 数组并调用 `SetObjectField` 替换该字段；成功且无异常的写入将返回标志置真。原指令夹具记录了真实 JNI 槽位 1152/1160/256/832 等，验证两次替换、空集合、错误 Map 类型及两种 values 分派。

这不是调用 `Map.clear()`，也没有证明会删除 ART 中已安装的所有 hook；其可证效果是对找到的回调容器字段写入空数组。

### 2.5 栈回退

`0x25dc1c` 走 `Thread.currentThread().getStackTrace()`，读取每个 StackTraceElement 的 `getClassName()`。比较使用固定前缀 `de.robv.android.xposed.XC_MethodHook` 的长度；匹配后全局置 3。原指令夹具以带 `Extra` 后缀的类名确认这是前缀比较，C++ 用有长度边界的字符串比较表达它。

## 3. 七条虚拟环境 / Superuser 路径

`0x30c03c` 按以下固定顺序构造七个字符串并扫描：

| 顺序 | 路径 |
|---:|---|
| 1 | `/guestOSInfo` |
| 2 | `/system/priv-app/vmos-pro-intent` |
| 3 | `/system/priv-app/romex` |
| 4 | `/sdcard/vphone_space` |
| 5 | `/system/app/Superuser` |
| 6 | `/system/priv-app/Superuser` |
| 7 | `/data/app/VPhoneQuickHelp` |

`0x30f590 → 0x311970` 为 `fstatat(-100, path, &statbuf, 0)`，即 AT_FDCWD、flags=0；每次缓冲区清零。ARM64 syscall 错误范围转换成 errno 和 -1。只有返回 0 视为命中，失败继续，首次命中短路。flags=0 意味着采用跟随符号链接的 stat 语义，不应改写成 lstat，也没有“路径必须为普通文件”的条件。所有失败返回假，包含权限拒绝等失败，不等同于证明路径不存在。

消费者 `0x408880` 构造 **event19** 的布尔结果。重建额外返回首个命中索引和尝试数以便测试；这两个辅助字段不是原件的网络字段。

## 4. maps：独立 event20 reader

`0x2d46ec` 使用 proc 路径辅助函数加 `/maps`，打开成功条件为 fd>=0；`fdopen("r") → getline` 循环读取。每条长度大于零的记录均执行 `line[len-1]=0`，末行即使没有换行也丢掉最后一个字符。

解析格式为 `%lx-%lx %4s %lx %x:%x %lu %n%*s`，检查 **sscanf 返回值 >=6**。`%n` 在 inode 之后才赋值，且不增加转换计数。六字段残缺行可能使用上一行的 n，首个此类行则可能读取未初始化值。源码使用可选 `initial_n` 表示这条边界；未给定有效 n 时返回 incomplete，不复制越界读取。测试显式设置 n=0 的结果与原指令夹具对照，不能把这个零解释成原件稳定初始化。

权限第三个字符必须是 `x`。跳过 ASCII 空白后，只对以下路径类型计数，且 `uint64_t(end-start)>0x5000`：

- 空路径：匿名计数 A 增加。
- 包含 `/dev/zero (deleted)`，或以 `[anon:` 开头：命名特殊映射计数 B 增加。

因此恰好 0x5000 不计数；end<start 的无符号差值仍可通过阈值。原指令夹具覆盖这两项、非执行权限、普通 `/data/app/a.so`、两类特殊路径和缺换行尾行。

成功收尾为 `state+20 = uint32_t(B - state+16)`、`state+24 = A`；无钳制，baseline 大于 B 时回绕。`0x2e3020` 构造器将 +16/+20/+24 初始化为 0；本次未穷尽 +16 的全部后续写入者，源码将 baseline16 保留为显式输入。

进入 reader 先清 +20。**打开失败保持旧 +24**，并向结果向量追加诊断 `8)`。该文字已执行原 getter `0x2d8a4c` 和字符串构造链 `0x2dea08` 验证，既有 `93 8c bd` 密文最终形成短字符串 `38 29 00`；不是猜测的 errno 或 “-1”。

函数还解码 `/data/app/`、`/data/data/`、`/data/user/`、`/packcache/`、`/lib`，末端存在去重代码，但已见正常循环没有向输出向量追加普通映射路径。字符串存在和保留的容器代码本身不证明额外过滤规则。`0x40df60` 将两项计数及向量交给 event20。

## 5. status / 调试状态

`0x3135e0` 使用 proc 路径辅助函数加 `/status`。fd<=0 调用异常处理 `0x3ee9fc(5)`，包括有效但为 0 的文件描述符。这里没有将它修正成 fd<0。

内联读取逻辑 `0x3170a8` 每次最多写 511 字节并加 NUL，保留换行。每个块按顺序处理：

1. 寻找 `TracerPid:` 子串；找到便从**绝对索引 11**取后缀，按十进制 `stoi` 解析并返回真实数值，包括 0。不是从命中位置加 11。
2. 否则寻找 `State:`；从绝对索引 7 取后缀，与 **`t`** 和 **`(tracing stop)`** 做完整相等比较。相等返回 **6**。
3. 都不命中则继续；EOF 默认返回 **-1**。

`State:\tt (tracing stop)\n`、`State:\tt\n` 都不等于两个完整常量，通常仍由后续 TracerPid 行决定结果。无换行的 `State:\tt` 则返回 6。`xxTracerPid:\t9\n` 的固定索引产生 `:\t9\n`，属于解析失败边界。C++ 将 stoi/范围异常转为 parse_error；不声称复制原件异常展开与异常处理全过程。

消费者 `0x317ef4` 在环境线程循环内比较**有符号结果 >0**，阳性调用 `0x3ee9fc(5)`。四库完整性检查与它同线程，但本次只核对调试消费分支；没有据此补入现代版本的 seccomp/SIGSYS 链，也未重建终止后端。

## 6. 混淆、guard 与现版区别

前轮已验证 UPX 外壳；本轮从已解包 ELF 和独立 IDB 副本继续，不改样本指令。内层控制流平坦化、魔数状态、重复跳转、SP 扰动、真假代码交错、XOR/TLS 字符串及 B 跳板仍大量存在。多个 Hex-Rays 输出出现 bad-SP、错误参数或串入无关函数尾部，证据保留这些原始诊断；源码重建依据关键汇编和受控原指令执行纠正，未将漂亮伪代码视为证明。

常见入口 guard 读自身前三条指令：首字 `>>26==5` 检测 B；首字 `>>21==1697` 检测 BRK；第二或第三字 `>>10==3508160` 检测 BR。命中走 abort/对应异常跳板。它是局部入口指令形状检查，不能提升成完整代码哈希或所有 hook 形式检测。`TPIDR_EL0+40` 的栈保护和 emutls 初始化标志分别是运行时机制，不能都称为反调试。

与已研究现版 **PSR_20260211.5223e3a** 的比较限于已有证据：

| 项目 | 本旧件 | 已有现版研究 |
|---|---|---|
| TracerPid | 511 字节行块，固定 substr(11)，stoi，额外 State 精确分支 | 一次 read<=2047，全文 marker，atoi 式32位回绕；已有链不含本 State 分支 |
| maps event20 | getline，末字节无条件删除，sscanf>=6 | 独立 reader 一次分配0x20000，循环读至0x1ffff；解析器不是本 sscanf 实现 |
| maps 计数 | 执行权限、size>0x5000、空/特殊路径、B-baseline 与 A | 这些已证计数语义相同；不要将 event20 与现版四库 maps parser 混为一条 |
| Java 框架链 | 固定 Xposed/Epic 名称、反射回退和实际字段写入，event24 | 已研究 event22 接收外部类名输入；未以此排除现版其他位置仍有 Xposed 检查 |
| 七条路径 | 完整顺序、fstatat 参数与 event19 已闭合 | 既有专项没有给出可逐项对应的同一七条路径，暂不推断增删 |

旧版 overview 在归档 `08_history/prism_old_overview/` 原样保留，记录上一轮更广的研究；本轮新增源码与结论仅覆盖指定检测。

## 7. 源码、验证和交付边界

源码独立放在 `01_source/research/prism_old_checks_20261018/`：两个头文件、三个实现、两组测试和一个构建脚本。没有复刻全库混淆模板、通信协议、UI、后台轮询和 SDK 缓存。

- `checks.cpp`：七路径状态机、maps/status 解析、入口 guard 纯谓词。
- `xposed.cpp`：真实 JNI 适配、反射字段/方法、Epic 家族、回调替换、栈和 token 缓存。
- `native.cpp`：Android/POSIX 采集；异常结果返回给调用者，未连接原件终止操作。
- `tests/core.cpp`：38 组断言，主要预期来自原指令夹具；`tests/jni.cpp`：12 个宿主 JNI 场景。

宿主测试均通过；使用 NDK 27 的 clang、C++17、`-O2 -Wall -Wextra -Werror` 完成 **ARM64/API24 共享库链接**。Android 产物仅交叉编译，未执行。证据中另有原指令 JNI、反射、maps、status、stat 参数和诊断文字验证。

JNI 源码使用 RAII 释放引用、对部分缺失对象/字段提前返回；原件个别空指针、异常 pending、OOM、混合 value 类以及并发状态竞争没有穷尽，因此异常路径不宣称逐指令等价。反射输入来自合成 Java 对象；真实 ART 版本和隐藏 API 可用性仍需要设备环境验证。baseline16 后续写入者、ART 枚举和终止后端是明确外部边界。

Git 保存可浏览的源码、报告、精简证据及验证脚本；版本化 Release 保存此专题完整冻结包、所选原始/解包样本、一个最新标注 IDB、前轮旧件历史证据、SHA-256 清单和验证记录。旧 r1 的 tag、归档和应用版本 pin 保持原有含义。
