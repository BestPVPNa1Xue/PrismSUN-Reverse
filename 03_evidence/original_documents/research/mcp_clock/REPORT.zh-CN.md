# PrismSUN `.mcp` 文件链与时钟链还原报告

日期：2026-10-17（Asia/Shanghai）。样本 `D:\PrismSUN\libprism-sun.so`，SHA-256 `92e7d4adda7e222aa9dce389009a186adabb2602b80d618d417e0f6d509adaf4`，Android AArch64 ELF，地址均为 imagebase=0 的 VA。

## 1. 结论与完成边界

本轮从前一会话的 `work/fresh`、数据库打包副本和工作目录证据继续，只研究两条指定链，未向上报/网络继续展开。

1. `.mcp` 本地链闭合为：两遍 `/proc/<pid>/fd` 符号链接枚举 → 特殊标记文件产生前缀 → 严格后缀/字节前缀筛选 → `MCPK` 文件头 → offset 24 的最多 64 字节文本 → `basename:文本` → 保持顺序和重复项的字符串数组 → kind 0 / event 32。
2. 时钟链闭合为：`[4,1,2,3]` 优先顺序取纳秒时间 → 失败再尝试 MONOTONIC → 纳秒 LE64、PID LE32、系统随机 20 字节 → Botan AutoSeeded_RNG / HMAC_DRBG 的附加输入 → RNG 输出。原件优先 HMAC(SHA-512)，创建失败再试 HMAC(SHA-256)。这条已定位链是随机数生成支持逻辑，没有发现时间差阈值、回拨/变速裁决或事件编号。
3. 两条链的 C++17 实现和可运行测试已经交付，并完成 Windows/Android ARM64 构建。本轮结论是指定本地链的静态语义闭合，不是对整个 SO 的运行时、OOM、并发、ABI 或异常 ABI 等价证明。

## 2. `.mcp` 文件链

### 2.1 路径构造和第一遍扫描

`0x5fe6c4 → 0x5feca8` 直接 getpid；`0x5fea58` 拼接解码的 `/proc/` 与 PID 十进制字符串。两处独立解码器 `0x319fa4`、`0x31ad44` 都得到 `/fd\0`，所以准确目录为 `/proc/<pid>/fd`，不是未经验证的 `/proc/self/fd`，也不是任意外部存储目录扫描。

`0x30bb2c` 通过 `0x30ddd8 → 0x3166c4` 打开目录，Android flags 为 `0x4000`（O_DIRECTORY，O_RDONLY 为 0），随后 fdopendir/readdir。只处理 d_type==10（DT_LNK）；不会为 DT_UNKNOWN 追加 stat。链接读取为 `readlinkat(AT_FDCWD, path, buffer, 4096)`。负返回跳过当前项。

匹配条件是**严格、区分大小写的后缀** `/PrismSUNScripts.mcp`。第一次匹配即关闭目录并返回；不搜集所有标记文件。对命中路径再次从 offset 0 查找标记的第一次出现，随后执行：

```cpp
prefix = target.substr(0, target.find("/PrismSUNScripts.mcp") - 1);
```

`0x30bf80` 明确为 `SUB X2,X8,#1`；`0x18a478 → 0x745934` 证实第三参数是 substr 长度。因此 `/abc/PrismSUNScripts.mcp` 产生 `/ab`。这是实际截取行为，不能“修正”为父目录 `/abc`。marker 在 offset 0 时长度无符号回绕为 npos，substr 返回整个路径。标记第一次出现和最终后缀可为两个不同位置，原件采用第一次的位置。

打不开目录、fdopendir 失败或找不到标记，返回空字符串。第二遍仍继续；空前缀对任意字符串成立。

### 2.2 第二遍扫描和匹配

`0x30b278` 先构造空 vector，调用上面的前缀获取，再重新构造 `/proc/<pid>/fd` 并独立打开、枚举。两个时刻的 fd 列表可能不同。

每个 DT_LNK 的 target 必须同时满足：

```cpp
target.ends_with(".mcp") && target.starts_with(prefix)
```

原件为 C++17 之前的辅助函数实现，上式只是逻辑表达。`0x30e5b0 → 0x31685c → 0x237c04` 取 `length - suffix_length` 后比较；`0x23f268 → 0x2379ec` 从 offset 0、按 prefix 长度比较。共同下游 `0x237b0c → 0x1d579c` 是 substring/view compare + memcmp，不是包含匹配。

- `/abc/a.mcp (deleted)` 不满足末尾 `.mcp`。
- `.MCP` 不匹配 `.mcp`。
- 前缀是普通字节前缀，不验证路径分隔符边界。
- 不去重，不排序，多个 fd 指向同一文件会出现重复字符串。
- readlink 失败跳过该项；第二遍目录打开失败时返回空列表。

### 2.3 文件头与文本

`0x30e700` 用解析后的 target 路径重新 open，**不是读取 fd 链接本身**。模式只读。读取 4 字节，每字节 XOR `0x07`，然后与运行时解码的 `JDWL` 比较。因此原始文件头为：

```text
文件字节：4d 43 50 4b   MCPK
XOR 07 ：4a 44 57 4c   JDWL
```

旧 Hex-Rays 输出中的 `$BI` 来自对 `0x7ac535..537` 初始值的错误常量折叠。汇编 `0x30e8e0..0x30e904` 是逐字节读取运行时解码后的四字节；不能将旧伪代码字符串作为最终校验常量。计算和原始字节保存在 `evidence/decoded-constants.json`、`focus-4.json`、`asm-0x30e700.json`。

头部匹配后 `lseek(fd,24,SEEK_SET)`，循环最多 64 次，每次 read 1 字节。读到 NUL 停止，否则追加原字节，不对正文 XOR、不跳过中间 NUL。最终关闭文件并得到该文本字符串。

原件没有检查上述 read/lseek 的结果，需区分：

| 情形 | 原件/重建行为 |
| --- | --- |
| open 失败 | 返回空文本 |
| 已知头字节不匹配 | 返回空文本 |
| 头部短读、未提供的字节参与比较 | 依赖未初始化栈；重建标记 IndeterminateStack |
| seek 失败 | 原件继续从现有游标读取；重建保留并标记 ignored_io_failure |
| 第一正文 read 失败/EOF | 依赖未初始化栈；重建标记 IndeterminateStack |
| 已读非零字节后 EOF/失败 | 上一字节留在栈槽，继续追加，最多累计 64 字节 |
| 正文首字节 NUL | 合法空文本 |
| 连续 64 个非零字节 | 原样取前 64 个 |

### 2.4 输出映射

调用点 `0x30b7f4` 用 X8 单独指定解析文本返回对象；原 target 在另一个对象中。之后：

1. `0x745e14` rfind('/')。
2. `0x18a478` substr(last_slash+1)，移回 target 对象。
3. `0x746084` 追加解码的 `:`。
4. `0x1db574` 追加解析文本。
5. `0x31b324 → 0x30ecf4` vector append。

例如 `/abc/a.mcp` 中 offset 24 文本为 `Demo` 时，事件项是 `a.mcp:Demo`。若 open 失败或头不符，仍加入 `a.mcp:`，没有以文本为空为理由跳过。特殊标记文件本身如满足第二遍条件也可进入结果。

`0x632054` 对 vector 逐项构造 cJSON string 并加入数组，调用 `0x634e84(32, payload, ...)`。即使没有记录，也生成空数组事件；本链没有首次/变化哈希抑制。

重建 API 返回载荷 JSON 数组；演示 CLI 的 `{event:32,payload:...}` 是易读包装，**不是已经恢复的新网络格式**。本轮止于本地结果对象。

## 3. 时钟链和真实消费者

### 3.1 时钟选择与回退

`0x140c9c` XOR 解码出四个 int32 ID，逐个清零 timespec 后调用 clock_gettime；遇到第一个成功即返回 `sec*1000000000 + nsec`。

| 顺序 | ID | Linux 名称 |
| --- | ---: | --- |
| 1 | 4 | CLOCK_MONOTONIC_RAW |
| 2 | 1 | CLOCK_MONOTONIC |
| 3 | 2 | CLOCK_PROCESS_CPUTIME_ID |
| 4 | 3 | CLOCK_THREAD_CPUTIME_ID |
| 回退 | 1 | 0x744750 再次调用 CLOCK_MONOTONIC |

四次失败后回退仍失败，会抛出带 `clock_gettime(CLOCK_MONOTONIC) failed` 的系统错误。0x140f44/0x21f710 解包纳秒 count，没有额外单位缩放。算术使用机器字回绕，源码用 uint64_t 明确表达，避免 C++ 有符号溢出。

### 3.2 32 字节附加输入

`0xf5198` 先调用目标 RNG 虚表 +16，确认是否 accepts_input。

| 字节范围 | 来源 | 写入 |
| --- | --- | --- |
| 0..7 | 0x140c9c 纳秒时间 | LE64，0x228640 → 0x1d6994 原样 64 位存储 |
| 8..11 | libc getpid | LE32，0x228860 → 0x1a3d60 原样 32 位存储 |
| 12..31 | 全局 System_RNG_Impl | arc4random_buf 填充 20 字节 |

全局对象 `0x79d450` 的 vptr 为 `0x78fb68`，+64 指向 `0x19b244`；该函数最终调用 `arc4random_buf(out,len)`。RTTI `0x3d755` 为 `Botan::(anonymous namespace)::System_RNG_Impl`。这纠正了上轮把 20 字节保留为未知辅助数据的状态。

`0xf5630..0xf5640` 恢复的虚调用参数是 `(rng, output, output_length, auxiliary, 32)`。其中 output 和 output_length 来自调用者，32 字节是附加输入，并非最终输出，更不是检测事件。

`0xf4f9c` 的分派：调用者提供非空 additional input 时，走 `0xf5734` 直接传入；否则走上述 timestamp 路径。目标 RNG 不接受输入时不获取时间/PID/20 字节，直接用空输入生成。请求输出 0 字节仍可构造附加输入并让目标吸收。

### 3.3 AutoSeeded_RNG / HMAC_DRBG

RTTI `0x3d57d` 为 `Botan::AutoSeeded_RNG`；其 +8 的拥有对象由 `0xf3b4c → 0x13430c` 构造，vptr 为 `0x78fa50`，对应 RTTI `0x3d61e` 的 `Botan::HMAC_DRBG`。

`0xf3cdc` 的两组字符串解码依次为 HMAC(SHA-512)、HMAC(SHA-256)，前者创建失败才用后者，两者失败则 Internal_Error。本重建同时实现两种 SHA-2/HMAC；正常选择 SHA-512，Hash 参数可显式选择后备分支。

HMAC_DRBG 初始化 V 为全 1、MAC key 为全 0，安全强度为 256 位；System_RNG 提供 32 字节 seed。AutoSeeded_RNG 初始化时会强制播种并生成、丢弃 1 字节（0xf4388/0xf49c4）。构造器调用点 `0x44c5e0`、`0x5b831c`、`0x56f54c` 均传入 0x400，所以 reseed_interval 为 1024。max_number_of_bytes_per_request 为 0x10000（65536）。

目标虚表 +64 为 `0x185168`：加锁后处理长度。

- 输出为空：调用 update(input)，输入长度至少 32 字节时把播种计数设为 1；这里不执行 PID/计数检查。
- 输出非空：`0x184994` 按 65536 分块，每块调用 `0x184df0`，检查 PID 和计数，必要时重新播种。附加输入仅用于第一块。
- 已播种、PID 未改变、counter<interval：counter++。否则记录 PID、counter=0，从 System_RNG 取 32 字节，更新状态，counter=1。输入源失败传播，不能伪造播种成功。
- 在这个 AutoSeeded_RNG 构造分支，备用 Entropy_Sources 指针为 null。通用 Botan Stateful_RNG 的其他外部熵提供者分支不属于此实例。

`0x1357ec` 的 update 与 `0x1352b0` 的 generate 是标准 HMAC_DRBG 结构：

```text
Update(data):
  K = HMAC(K, V || 00 || data)
  V = HMAC(K, V)
  若 data 非空:
    K = HMAC(K, V || 01 || data)
    V = HMAC(K, V)

Generate(n, data):
  若 data 非空: Update(data)
  重复 V = HMAC(K,V)，取前 n 字节
  Update(data)
```

因此时间值的作用已追到实际 RNG 状态和输出。原路径中没有用两次时间相减，没有超时阈值判作弊、没有检查时钟倒退；不能把这条链命名为“变速检测已确认”。此判断限定于已追踪入口，不宣称全库不存在其他时间用途。

## 4. C++ 结构和有意差异

| 文件 | 对应范围 |
| --- | --- |
| src/mcp_chain.cpp | 两遍枚举、readlink、头部与文本、输出拼接、event32 数组 |
| src/clock_chain.cpp | 时钟优先级、aux32、虚接口分派、具体 DRBG 状态/计数/分块 |
| src/crypto.cpp + sha_constants.inc | 标准 SHA-256/SHA-512/HMAC 的便携实现 |
| tests/unit_tests.cpp | 系统调用与文件系统夹具、错误/边界/分派检查 |
| tests/oracle_tests.py | 独立 Python hashlib/hmac 对照 |

有意差异明确如下：

- 不复制全库重复的函数入口指令自检、控制流平坦化、栈保护与混淆解码器；保留其后的业务语义和原常量，不生成原地址 patch。
- FileOps/Services 是可替换依赖，NativeFiles 在 Linux/Android 使用对应 syscalls；不模拟原 libc++/cJSON 对象 ABI 和 OOM 异常 ABI。
- readlink 最长 4096 字节时，原件 4096 字节数组后追加 NUL 存在越界；重建额外分配 1 字节。不复制越界写。
- 初始短读涉及未初始化栈，源码显式表达“不确定”，不选择人为栈值冒充原件。对于该批扫描不能生成唯一 event payload。
- Windows 用 steady_clock/BCrypt 运行可移植演示，准确 Linux ID 顺序由夹具检验。Android 原生 adapter 只完成交叉编译。
- 两份 SO 面向源码接口，不承诺直接替换游戏库；本轮不分析上报传输、宿主发送或服务端规则。

## 5. 验证与完整性

实际执行：

```powershell
& D:\PrismSUN\research\mcp_clock\scripts\build.ps1
& 'D:\Python 314\python.exe' D:\PrismSUN\research\mcp_clock\tests\oracle_tests.py
```

结果：Windows 46 项检查 PASS；独立加密对照 98/98 PASS。对照覆盖两个 SHA、两个 HMAC 和 DRBG 的 0/1/31/32/63/64/65/128/1000/65536/65537/131073 字节请求，附加输入为空和 32 字节两类。Android ARM64/API24 CLI、测试程序和两份独立 SO 编译成功，readelf 核实 ELF64/AArch64。宿主 clock 演示实际运行成功。

这些测试没有运行原始 ELF；不宣称 144 次原件对照或真机实验。原件闭合依据是保存的 IDA 汇编、虚表、RTTI、调用点与字节解码。对照测试证明重建代码与独立标准算法/夹具期望相符。

`prism-mcp-clock.i64` 保存 19 个语义命名和关键注释。入口副本来自上轮打包数据库，上一轮仍驻留但未能重新采用的 worker 未被终止。原始 SO、原始 i64、上一轮打包副本的前后哈希见 protected-before.json / protected-after.json，最终验证记录见 verification.json。

## 6. 交接状态

本轮要求的两条本地链、可编译源码和上述验证均完成。后续接续请先读本报告，避免继续沿用“扫描目录未知”“$BI 文件头”“20 字节辅助数据未知”“时间链疑似变速检测”等历史条目。

仅保留证据类型边界：实际 Android 运行、非确定栈值、并发竞争/资源不足、整库函数入口保护没有作为等价目标验证。上报链按本轮范围没有继续。
