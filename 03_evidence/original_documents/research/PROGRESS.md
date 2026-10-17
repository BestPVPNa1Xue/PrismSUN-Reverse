# PrismSUN 研究检查点

## 2026-10-18 四条主链收口与 C++ 重建

单线程、仅 IDA Pro MCP 与本地证据，无 REA、无子代理、未运行原 SO/原指令仿真/Android 产物。最新入口：[四链报告](chain_closure_20261018/REPORT.zh-CN.md)、[静态笔记](chain_closure_20261018/CHAIN_NOTES.zh-CN.md)、[源码与编译](chain_closure_20261018/README.md)。本轮副本 prism-chain-closure.i64 已保存，保护文件核验4/5匹配；原SO/原IDB不变，历史environment-memory库哈希变化，独立worker曾打开后退出，不能断定仅元数据变化。该异常及哈希见 verification.json，完整性验收未标全PASS。

TracerPid：一次read<=2047，首marker全文子串，open/read失败-2、marker缺失-1、atoi式32位回绕；每个普通循环signed >0才本地终止。seccomp：status variant错误与字段缺失已分清；reason 0/2/3/4/10/11/12已闭合，handler 0/1 inactive，路径按首个半开区间定位；主动probe临时SIGSYS handler+openat，不安装filter，恢复失败不改变原返回。上层layer0异常诊断5006。未运行必要probe时模型明确incomplete。

四库maps：整行strstr、deleted排除、空needle返回原haystack、无条件截掉最后一字节、sscanf七字段、保序/路径空格已恢复；复用既有ELF section/CRC和四库循环模型。event22：输入type3请求JSON至少两项，首项number低字节taskID、第二项array；任务35借用配置，非string终止列表、FindClass异常Clear继续、重复保留。工厂注册与构造静态链补存；真实类名单是请求输入，没有固定名单可从本SO推出。

新增 C++17 核心、Android ARM64 direct-syscall采集与SIGSYS backend、JNI adapter。宿主核心112项及JNI mock10项PASS；Android ARM64/API24 SO和两份测试程序交叉编译成功，siginfo/ucontext及JNI槽偏移断言通过。没有APK工程，也没有真机等价结论；原件旧704/404等结果未重跑。

event20扩查：独立reader循环读取最多0x1ffff，数值为B-state+16与A，失败可能保留旧+24，正常未见附普通maps路径。state+16后续来源、原诊断文字、独立raw数字scanner边界仍待闭合；代码只重建显式输入下的计数消费。宿主门控0x41de58、全库自检/其他任务与端到端传输仍按旧审计保留，不将四条主链收口称作全模块穷尽。

## 2026-10-18 剩余检查点与覆盖审计

单线程、仅 IDA Pro MCP 与本地证据审阅，无 REA、无子代理、未执行原件或重跑旧测试。完整评估见 [覆盖审计报告](coverage_audit_20261018/REPORT.zh-CN.md)。本轮从最新 MCP/时钟数据库复制 `coverage_audit_20261018/prism-coverage-audit.i64`，按既有 FDE 补齐部分定义并保存，未改原件和历史数据库。

任务侧交叉核对得到 ID 17、33、34、35、36、37、38、39、40 的9项静态对应。其中8项对应既有10个事件号；任务36的已恢复正常执行路径 `0x73ce64 → 0x6d49a8` 返回 kind1/None，不能据此新增一个检测模块。原始取证与结构化映射在审计目录 evidence/。该表不是全库检测总表，环境线程、入口保护、本地终止与间接配置仍需单独核算。

优先剩余项：event20 maps语义及+20/+24来源；seccomp/SIGSYS原因码 `0x471c8c` 与上层消费者；event22实际配置来源/类名单；四库maps过滤器 `0x5f917c/0x5fb6b0`；宿主门控 `0x41de58`。MCP本地链、已定位RNG时钟链、CRC基线、设备ID回退及APK证书摘要对象已由专项解决，不再按旧未知项重复研究。多槽writer、完整握手、逐事件传输、真机与服务端边界仍缺证据。

## 2026-10-17 MCP 文件链/时钟链专项完成

接续会话 `01a14573-7a3b-7463-9e36-0a68db497e5b`，按新范围停止扩展上报链。仅 IDA Pro MCP，无 REA、无子代理。以 `mcp_clock/REPORT.zh-CN.md`、`mcp_clock/README.md`、`mcp_clock/evidence/INDEX.md` 为最新结论；旧“目录/头部/20 字节未知”等条目已被本轮证据替代。

MCP：两遍 `/proc/<pid>/fd`，d_type==10，readlinkat；第一遍严格后缀 `/PrismSUNScripts.mcp`，首次命中后 `substr(0, find(marker)-1)`，不是规范化父目录。第二遍 `.mcp` 严格后缀 + 普通字节前缀。原头为 MCPK，XOR07 后 JDWL；旧 Hex-Rays `$BI` 是错误常量折叠。偏移24读最多64字节，到NUL停止，原 read/lseek 不检查；EOF可重复前一字节。输出 basename + ':' + text，open/坏头仍保留 basename:，保序不去重，无marker的空前缀放行所有.mcp。数组生成 kind0/event32，空列表也生成事件。

Clock：0x140c9c 依次 [4,1,2,3]，失败后再试MONOTONIC，仍失败抛系统错误。aux32是LE64纳秒+LE32 PID+arc4random_buf20字节。RTTI/vtable已闭合到System_RNG_Impl和AutoSeeded_RNG/HMAC_DRBG，优先HMAC(SHA-512)，后备SHA-256。构造时播种并丢弃1字节，三处调用均interval0x400；65536字节分块，只第一块使用附加输入；PID变化或计数到阈值重新播种。此链为RNG支持逻辑，无时间差或作弊裁决证据。

C++17 源码在 `mcp_clock/src/`，Windows CLI/unit tests、Android ARM64/API24 CLI/unit tests和两份独立SO已构建。宿主46项检查PASS，独立hashlib/hmac对照98/98PASS；本轮未运行原ELF、未做原件差分、未真机运行Android。短读依赖未初始化栈时返回显式不确定，不伪造事件；不复制原readlink终止符越界写或全库入口保护。专项IDB `mcp_clock/prism-mcp-clock.i64`，会话 `6e90ea58`，已保存19个命名与关键注释。完整性和保护文件哈希见 `mcp_clock/evidence/verification.json`、`mcp_clock/manifest.json`。

## 2026-10-16 环境/内存/输入法专项续接

从会话 `01a14039-f500-7131-9dd3-a596b6eb2498` 的中断源码继续。本轮遵从用户要求，只用IDA Pro MCP进行逆向，没有REA调用，没有子代理。报告与构建入口：`environment_memory/REPORT.zh-CN.md`、`environment_memory/README.md`。专项数据库会话 `fe3803f0`，`prism-environment-memory.i64` 已保存六个按FDE恢复的函数边界。

确认并修复旧草稿：0x44d0b8对整批区段选同一个基址，+56备用基址跨调用保留且消费一次；首个可读可执行候选完成后立即返回。没有备用基址时并不因超出map.end就跳过摘要。路径一致性检查先于权限检查，路径改变有本地终止调用。返回57实际由候选vector.empty触发，不仅是打开失败；非空但无可执行候选也可能返回46。模型读取失败以complete=false/code=nullopt单独表达。

输入法是getInputMethodList/getServiceName，不是当前默认输入法。+560/+564保存哈希/首次状态；首次34、变化35、同值kind1、JNI获取失败0xBBA。KeyMapper联合规则、Xposed具体名单与服务端裁决未证实。四库基线最多两个SHF_EXECINSTR区段，CRC32大端摘要按小端u32读取，随后XOR掩码；libmediandk非46终止，其他三库仅12锁存。

新源码最终Windows EXE/DLL、Android ARM64/API24 executable/SO已构建；宿主73检查通过（含复用的6个摘要+9个IME哈希保存结果比对），JNI mock8场景通过。原件6/9测试记录复用，本轮未重跑仿真。旧seccomp704、class404等套件未重跑。Android仅交叉编译，未真机运行。核验记录为environment_memory/evidence/verification.json；源码/产物/证据清单为manifest.json。

剩余精准入口：0x5f917c/0x5fb6b0两个maps过滤器虽恢复边界，反编译仍有严重栈别名；0x471c8c原因码生产者仍有JUMPOUT；0x6ab3d8需运行时配置来源/具体类名单；event21/22/24/34/35未逐项完成到输出ring/真实网络的端到端回放。没有全模块等价或稳定绕过结论。续接应优先读专项报告，不再按下面历史条目重复已解决的基线/摘要工作。

2026-10-11 无障碍专项已交付：见 [专项总报告](accessibility/REPORT.zh-CN.md) 与 [构建/使用说明](accessibility/README.zh-CN.md)。REA 6.4.0 已实际完成原件 0x6cf0c8 / 0x31b73c / 0x6d4374 三项分析并关闭；哈希自动函数边界不完整，采用原 ELF/FDE/Unicorn 补足。原件与两个旧数据库 SHA-256 全部不变，新副本 accessibility/prism-accessibility.i64 已保存。

本地闭环：ELF 初始化注册 AccessibilityServiceChecker（ID38）→ JNI1.6 GetEnv/必要时 AttachCurrentThread → ActivityThread.getApplication → Context.ACCESSIBILITY_SERVICE → getEnabledAccessibilityServiceList(-1) → List.size/get → getId → modified UTF-8 strings → 原序 cJSON array + 排序副本 CRC32（逐项附NUL，Botan大端摘要按ARM64小端读，即bswap32）→ 首次25/变化33/相同kind1。单例+552初始0保存指纹、+556初始false保存首次标志。JNI环境失败为kind2/error0xBBA且状态不变。未见本链的KeyMapper专用比较，不能从采集推出服务端处罚。

新增可编译 C++：accessibility/src 下 core、jni、env、monitor 及 demo；Windows DLL/EXE、Android ARM64/API24 SO 均构建。原哈希42/42、原消费者与C++180/180、最终DLL75项指纹检查及42项原哈希回放、JNI adapter 8场景、env scope原指令6场景/C++6场景、14项JNI/VM表偏移静态断言、专属注册/工厂仿真均PASS。最终核验 evidence/final-verification.json：3个保护文件不变、22项manifest哈希匹配、23个文档链接有效。已完成测试不必重复。调度周期/具体timer callsite、服务端使用方式和实际Android设备结果保留未知；精准后续入口见 notes/scheduling.md。源码为语义重建，JNI显式异常/空值保护是增强，不是原件已证行为；不承诺ABI/OOM/并发等价。

2026-10-11 工具安装接续：REA 6.4.0 与独立 IDA 桥接已完成配置，最终验收 PASS（生产 MCP 170 工具/6 提示、CLI 反编译、ARM64 辅助库与原件 0xb59c0 分析、关闭清理、原件/数据库哈希保护）。本轮不推进反作弊判定结论。安装状态、验证证据、使用方法和回滚见 [REA 安装记录](tooling/rea/README.zh-CN.md)。重连/重启 Codex 后加载新 REA 工具。KeyMapper 是用户新增的待验证假设，不能把既有无障碍枚举/变化记录直接等同于特定软件作弊判定。REA headless 使用临时数据库；继续上一轮标注应使用原有 IDA 接口和 prism-analysis.i64。

本轮续接核验：8fcdbd7e 仍为活动分析副本会话，没有遗留测试/构建进程。状态偏移扫描已完成（110 分块、194 候选），已将事件 24 地址标签从 0x68cc74 修正为实际 0x68cc78，没有重跑。环境完整汇编确认共同单例 0x3b8c40，以及三条返回码 ==12 的置位路径：+216 对应 libc.so/state+264、+219 对应 libandroid.so/state+408、+218 对应 libart.so/state+336。具体库名复用已完成的 stage2_strings.json 调用端证据。比较器 0x44d0b8 含映射/区段摘要比较；摘要算法与基线初始化尚待原字节验证。

新增五个 FDE 函数定义并 idb_save 成功：0x3d764c..0x3d7dd0、0x3d832c..0x3d8750、0x418544..0x418fc4、0x419480..0x419e4c、0x41a260..0x41af28，连同 0x44d0b8 的反编译已导出。REPORT.zh-CN.md 和 README.md 已补入事件 22、404/404、JNI 偏移断言及三个系统库相关状态位。0x44c740 的 IDA 定义只有 0x30 字节，而 FDE 为 0x44c740..0x44cfa0，尾部 0x44ce78 已另定义函数，暂未合并，以免丢失既有边界信息。

事件 22 子集接续完成：class_probe_model.{h,cpp} 已还原并编译为宿主 DLL 和 Android ARM64 so，jni_layout_check.cpp 的四个 NDK 表偏移断言通过。test_class_probe.py 会话 64427 已退出 0，404/404 通过，记录为 differential_class_probe.json。执行原件事件 22 控制流及 0x2dce08/0x3079bc/0x307d30/0x301194 四个真实包装；显式模拟 JNI 返回值、获取、配置与容器操作。禁用配置输出空事件；JNI 获取失败走 0xbba 诊断且无事件；查询异常清除并继续；无异常非空结果释放局部引用后保留原列表项。没有具体目标类名单或网络传输结论。新的五个定义已 idb_save 成功。

最近接续（2026-10-05 17:00 后）：REPORT.zh-CN.md 和 README.md 已确认写入完成。报告 41 个证据链接及 README 2 个链接均存在；三个 build manifest 的 13 项源码/产物哈希全部匹配，原始 ELF 哈希匹配。既有五套测试未重跑。上一项 idb_save 成功，分析副本包含 0x2dce08、0x306df0、0x3079bc、0x301194、0x6b0998 的 FDE 函数定义及反编译导出。

本轮新增五个 FDE 函数定义：0x6ae288、0x307d30、0x3071a8、0x305790、0x6b0660。事件 22 的 JNI 包装已识别候选：0x2dce08 表 +0x30 的 FindClass；0x3079bc 表 +1824 的 ExceptionCheck；0x307d30 表 +136 的 ExceptionClear；0x301194 表 +184 的 DeleteLocalRef。正在做原指令验证和 NDK 头文件偏移核验。jni_find_class_asm.json 含 278 条 IDA 指令记录，但跳过了部分数据定义的代码字节，尤其 0x2dd330 分派跳转；其伪代码只有 JUMPOUT，明确不是完整逻辑。

日期：2026-10-05。原始 ELF 与原始 i64 保持不变。分析副本：prism-analysis.i64。

已完成：样本哈希、IDA 概览、三导出入口定位、关键函数反编译、ELF/FDE 清单、函数前缀隔离仿真。直接 BL 目标已加入候选集（16,217 个）；完整扫描得到 391 个写入函数、522 条 ASCII 片段；核心补扫得到 127 个写入函数、38 条片段。上述扫描已经结束，不需要重新运行。

已确认：Android AArch64；入口指令自检；共享缓冲区地址；时钟采集；SDK 属性查询；静态链接 Botan 类型信息。

最近完成操作：0x2db470、0x2ac2e0、0x2b4b08、0x2bba34、0x4c4f88、0x4c546c、0x59240c、0x47fafc 的反编译均已写入 decompiled/。恢复检查确认会话 8fcdbd7e 仍存活，分析副本已打开；原始数据库没有覆盖。

第二阶段解码已完成：0x2bc258 -> 0x2bc7b0 使用 64 位密钥的低端序循环字节 XOR，随后清除对象的加密标志。308 个包装函数已执行；116 个候选中 115 个有调用端数据流证据。stage2_strings.json 是主要字符串证据；未验证的 _.+xH 排除在结论之外。上述扫描已结束，不重复运行。

当前工作：追踪 TracerPid、seccomp、APK 签名块和 MediaDrm 设备标识的实际消费者，区分采集、判断与上报。已解出 ActivityThread、包管理器、sourceDir、无障碍服务、输入法、maps 路径、libminecraftpe.so 与运行时 JNI 获取等线索；Xposed 专项判定仍待证实。

待完成：业务调用链；Xposed/签名/设备采集证据；共享区格式；标准 C++ 子集及测试；研究报告。

新增确认：shmFence -> 0x2b47f8(5) -> 0x2bba34 执行 DMB ISH；0x59240c 初始化两个 32 位字；0x4c89cc 消费共享区记录。入口自检的具体可达性尚需逐函数验证，TPIDR_EL0+40 属于栈保护，不作为反调试证据。

数据质量提示：FDE 与 IDA 函数集合均不完整，二者并非包含关系。第一轮解码文本多数属于库代码。当前没有全模块还原或等价验证结论。

恢复检查（2026-10-05）：8fcdbd7e 会话仍存活且未分析中；没有已知未完成的 shell 操作。idb_save 成功保存 prism-analysis.i64，包含 0x468a48、0x46d830、0x4181a0 新增函数定义。0x406068 的反编译输出曾被上游截断且有 SP 警告，后续已保存六页完整 IDA 反汇编（2799 条指令）。

本轮断点：Windows DLL 和测试程序已编译。第一次启动退出 0xC000007B；在当前进程 PATH 前置 D:\msys64\ucrt64\bin 后，同一程序通过 9 项检查及零长度调用。构建脚本已加入该运行库路径。ARM64 编译与差分测试接续执行；没有全模块等价结论。

新增链条：0x5a7be4 / 0x5ae1d4 获取 Widevine MediaDrm deviceUniqueId，0x4df3c8 经 0x5b9df4 处理后转十六进制。0x37843c / 0x4c0718 提取 APK v2 签名块中的嵌套数据，再经 0x3780ec 摘要与十六进制编码。两条链均被 0x7153a8 调用；继续分析其采集汇总和下游，尚未证实网络上报或信任判定。

本次恢复核验：宿主 DLL、测试程序、Android ARM64 辅助库均已构建；宿主测试通过 9 项及零长度调用。差分测试最终 169/169 通过，初次受预算限制的 1024 字节 XOR 个例已单独重试成功（590985 条指令），初次记录保留于 differential_initial.json。差分范围仅为 XOR / hex 函数体输出与尾部 16 字节保护区。

数据库已再次保存，包含 0x5b8a10、0x5b9674、0x635514、0x2d9160 与所有权包装辅助函数定义。环境检查调用 0x406068 后在 0x4106f8 比较结果，0x4106fc 使用有符号 B.LE；已证实消费者判定 TracerPid > 0，阳性路径写入数值 3。environment_asm.json 的实际行数少于工具计数，属截断记录，后续以分页完整记录为准。

0x7153a8 汇总设备标识（空值备用路径 0x4dfc3c）、APK 数据摘要、包名与 activity 相关信息；0x715df8 调用 0x634e84（X0=19）。该调用暂标记为结果对象构造候选，尚无网络发送证据。摘要名称正沿 0x5b8524 -> 0x5b8a10 -> 0x5cc270 -> 0x5b9674 -> 0x5cc27c 接续核实。

最近完成：environment_asm_0.json、environment_asm_256.json 与原 environment_asm_512.json 合计完整 866 条工具指令记录。摘要名称已解出 SHA-256：0x5b8a10 将 0x7af3cc 八字节变为 9c67beb8df0c75f1，0x5c433c 经 0x5cc540 -> 0x2bc7b0 用 f14339ed95ff2fcf 循环 XOR 得到 SHA-256 加零终止符。详见 digest_decode.json 与 0x5c433c_asm_0.json。

TracerPid 阳性路径的 0x4497e0 -> 0x4c3778 调用 0x4c40e0（getpid）、0x56b300 -> 0x4c4214（线程 ID 待继续汇编核实）、0x56b304 -> 0x4c3f38（tgkill，信号参数 9）及 0x4c49ac（exit_group，参数 2），随后还有 BRK 指令。此处属于本地异常终止路径证据，并非已证实的网络上报。0x5c433c 与 0x4c3778 按 FDE 边界定义成功，数据库已保存。

接续核验：宿主 observed_models DLL 已在中断前编译完成；本次保存数据库成功，包含 0x4c4214、0x47f2c8、0x3b3860 的定义。0x4c4214 经 0x4e0374 获取 gettid，-1 时采用 getpid。SHA-256 解码原指令仿真 3/3 通过，包含加密标志 1、3、0 和保护区检查。

seccomp_policy_asm_0.json 与新增 _256.json 合计 268 条记录，分页已完整。0x47e0a4 比较保留 32 位 layer+1 回绕，随后有符号比较。原因码分类函数 0x47f2c8 接受 byte 值小于 10。observed_models.{h,cpp} 为三个纯判定模型，测试脚本已创建，结果待接续。无障碍服务 / 输入法函数只确认枚举，作弊判定消费者仍待证明；maps 反编译存在 SP 和不可达垃圾代码问题。

恢复检查：中断前 shell 会话 80992 已退出，seccomp 聚合模型差分测试 704/704 通过，结果为 evidence/differential_policy.json；不重复该操作。三个纯判定测试此前 524/524 通过，正在对最终 DLL 补测以同步哈希。observed_models 新增第四个函数 prism_filter_policy，紧凑结构仅表达语义，非原件 ABI。聚合测试显式模拟状态获取、SIGSYS 获取、原因码产生和字符串操作，并非完整 seccomp 检测等价。

新增证据：0x46dc28 查询 SIGSYS (31)，0x46e824 用 X8=0x86 直接 rt_sigaction；0x466a00 为直接 openat 包装。无障碍服务消费者 0x6cf0c8 与输入法消费者 0x6f4218 对名称数组计算哈希，抑制未变化结果；首次/变化结果编号分别为 25/33 和 34/35，均调用 0x634e84。这支持结果采集与变化记录，尚未证实网络发送或作弊结论。0x468a48.json 反编译字符串被截断，保留为线索而非完整证据。

本轮恢复核验：shell 会话 43098 已退出 0，最终 DLL 的判定测试 524/524 通过；704/704 聚合测试同样已完成，不重复。当前进程只有 MCP 服务，没有遗留构建或测试进程。8fcdbd7e 已打开分析副本，is_analyzing=false；server_health 的 auto_analysis_ready=false，故不将数据库视为全局分析完毕。

结果对象修正：result_constructor_asm.json 包含完整 363 条记录。0x635144 保存 W0 低字节，0x635164 写零到 output+0，0x635168/0x63516c 将原事件字节写到 output+4；Hex-Rays 的 output+4=0 表达错误。19、25、33、34、35 实际保存在对象中。载荷位于 output+8，尚未证明网络传输。

共享缓冲区：shared_reader_asm_0.json 与 _200.json 合计完整 376 条记录。writer 在 +0，reader 在 +4，16 个 4096 字节槽自 +8 起。首槽 total(u32,+0)、type(u8,+4)、count(u8,+5)；每槽 length(u16,+6)、payload(+8)。count 为 1..16、total<=0xff80；available=(writer-reader) 的 32 位回绕结果，比较使用无符号 B.CS。每槽追加 min(length,0xff8)；累计长度不同于 total 时调用 resize。0x592270..0x592280 的 reader 更新是完整 32 位 reader+count，伪代码的字节截断错误。无效头丢弃当前队列，不完整记录保留游标。

新增函数边界按 FDE 定义：0x591164、0x51fc30、0x51f85c、0x4e0f04。它们的反编译仍有寄存器和参数混淆，原件 C++ 对象 ABI 待进一步验证。0x4cb88c 的分派器已保存，含 bad-SP 警告，仅作后续线索。

本轮完成：shared_ring_model.{h,cpp} 与 build_shared_ring.ps1 已写入，首次宿主/Android ARM64 构建均成功。test_shared_ring.py 的 shell 会话 80405 已退出 0，648/648 通过，证据为 differential_shared_ring.json。比较原件 0x591e24 控制流、分段追加长度、resize 调用、类型值、读游标和保护区；获取原子计数与 string/optional 操作显式模拟，不含载荷字节复制和并发等价。数据库已保存四个新增函数，不重复构建或既有测试。

clock_ids.json 已保存 MCP 原始字节、XOR 解码与 xrefs，四种 clock ID 为 4、1、2、3，对应 MONOTONIC_RAW、MONOTONIC、PROCESS_CPUTIME_ID、THREAD_CPUTIME_ID；失败回退到 0x744750。0xf5198 的时间/PID 汇总仍仅是熵输入候选，不标记时间作弊判定。

事件清单接续：0x632054 生成 32，0x650898 生成 20，0x66e838 生成 21，0x68cbe0 生成 24，0x6ab3d8 生成 22；五份反编译已保存。21 读取共享状态字节 +218/+219/+216，24 读取 +218；这些是状态消费者，状态来源待核实。22 沿配置列表和 JNI 包装查询目标，查询 0x2dce08 返回 decompilation failed，无数据库写操作。不可仅据此命名为 Xposed 检测。


## 2026-10-15 设备身份专项交付检查点

设备身份的详细进展已汇入 `device_identity/REPORT.zh-CN.md`、`device_identity/README.md` 和 `device_identity/evidence/INDEX.md`。不要仅凭旧的“未证明载荷交付”条目忽略专项新增证据：本次已在有界原指令 fixture 中串接 event 19、0x51e9c4 结果转换、紧凑 JSON、AES256-GCM packet 和单槽输出 ring；合成输入得到 221 字节 type 5 packet，sequence 7→8，与独立 oracle/C++ 输出一致。这仍不证明真实宿主网络上传或服务器封禁。

最终验证：`device_identity/evidence/verification.json` 为 117 项 PASS；来源入口 13 场景、event 基础6/边界9、session3、Activity7、packet3 等已保存。该数目是检查数，含保存结果一致性，不是117次真机或全链路运行。APK wrapper 的最低 1GiB 门槛已确认。多槽 writer 成功异常及 literal 0x3dc58 未解释，C++ 按4088字节协议分片，不宣称原件等价。0x56eae4 完整握手解析、宿主发送和服务端规则仍未知。

源码见 `device_identity/src/`，构建见 `device_identity/scripts/build.ps1`；Host executable/unit_tests、Android executable/shared library 已实际构建。原四文件身份在 `device_identity/evidence/before.json`、`after.json` 核对，专项新IDB保存了17个命名和5处注释。REA三份成功 dossier 在 `rea-evidence.json`，残留unknown在 `rea-final-evidence.json`，native session已关闭；`rea-session-install.json`只是失败记录。旧套件和本专项没有变化时无需重跑。交付完整性记录见 `manifest.json` 与 `delivery.json`；不再用历史 `prism-devicecheck.zip` 代替最新交付包。
