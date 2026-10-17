# 调试检测 APK 可实现程度评估

日期：2026-10-18（Asia/Shanghai）。范围：指定会话的最后一个已完成成果、当前工作区、已保存 IDA 证据、C++ 重建源码及构建清单。**本轮没有构建 APK/SO，没有运行原样本、原指令仿真、旧测试或 Android 产物。逆向工具仅调用 IDA Pro MCP，没有调用 REA。**

## 目标

**现有成果足以支撑一个具有真实采集能力、能够解释原分支与事件的 ARM64 调试 APK。它尚不足以支撑全量 Prism 复刻、通用外挂识别器或游戏进程/服务端判定预测器。**

指定会话最后的已完成回复是“四链收口与 C++ 重建”；再后面只有一次无成果的中断。最新依据为 [四链报告](../chain_closure_20261018/REPORT.zh-CN.md) 和 [静态笔记](../chain_closure_20261018/CHAIN_NOTES.zh-CN.md)。历史总报告、10月16日清单和10月18日早期覆盖审计中的部分“未知”，已被随后四链成果替代，不能直接累加为当前缺口。

## 假设与等级

默认目标是一个普通、独立安装的调试 APK，检测其自身进程；ARM64/API24 为现有原生构建下限，实际 targetSdk 尚未确定。Root、目标进程内加载、特权跨进程读取不作为默认条件。

“程度”按现有代码的工程成熟度评估，而不是未经测试的检出率：

| 等级 | 定义 |
| --- | --- |
| L0 | 当前没有已证实的该类检测规则；不能由相关字符串或支持代码补造 |
| L1 | 有片段或部分语义，关键输入、覆盖范围或判定仍未闭合 |
| L2 | 主要语义/核心模型可用，但真实采集、输入来源或平台组合仍需补齐 |
| L3 | 核心逻辑和 Android 采集/适配代码均已存在，具备 APK 接入基础；尚未完成真机验证 |
| L4 | 已在 Android 上验证采集、触发、错误、生命周期，并与原实现作相应范围对照 |

**目前没有任何一项具备 L4 的工作区证据。** L3 不等于 APK 已经完成；所有项目仍缺 APK 工程、Java/Kotlin→native 调用桥、界面、调度及设备验收。不能从宿主测试数量计算设备检出率或准确率。

独立 APK 与目标进程内检测的差别是实质边界：TracerPid、SIGSYS、maps/内存、fd、ClassLoader 均受进程上下文影响。同一台设备上两个应用的结果可以不同。无障碍/输入法属于系统服务可返回的信息，也受用户/配置文件、系统版本及调用环境影响。

API24交叉编译仅证明构建目标，不证明API24至最新Android均实测兼容。无障碍/IME已有接收显式Context的接口，APK可通过这些接口避免依赖ActivityThread隐藏API；这属于已提供的工程适配路径。真实类探测仍须保留线程/ClassLoader上下文。现有status路径使用getpid而非gettid，主动openat则发生在调用线程；应记录PID/TID，不能默认各线程的调试/seccomp状态恒相同。

## 逐项定位与能力

以下条目按用户能观察的能力展开；四库、seccomp 子步骤和 event19 字段有意拆开说明，不据此统计独立检测模块数量。

| 项目 | 等级 | 调试 APK 可达到的具体程度 | 无法由当前结果推出的结论 |
| --- | --- | --- | --- |
| TracerPid | L3 | 对本进程 status 进行原样一次读取≤2047字节，保留 -2/-1/0/正值、32位解析规则，按 signed >0 显示原本地终止条件 | 不能覆盖所有 Java 调试器、所有线程调试情形或所有 Hook；不能证明游戏进程未被调试 |
| Seccomp / Seccomp_filters / NoNewPrivs | L3 | 一次读取≤4095字节，区分采集失败与缺字段；显示 mode/count/NNP、layer、计数超限及聚合结果 | mode/NNP 在已追踪聚合器中不是独立作弊布尔；过滤器数量多不等于某个具体框架 |
| SIGSYS handler 与原因码 | L3 | 查询本进程 action，0/1视为inactive；按首个半开maps区间定位地址/路径，复现0/2/3/4/10/11/12及5006诊断条件 | 未定位到特定软件；handler获取失败在原聚合规则中不一定使acceptable变false |
| SIGSYS 主动 openat 探测 | L3，实验性接入 | 已有ARM64直接syscall backend，恢复临时handler的顺序、probe marker和返回值；显式启用后可观察该进程openat是否触发相应SIGSYS | 默认不开主动probe，必要时未执行应为未完成；不能证明所有seccomp动作或所有隐藏机制。实际信号并发/设备行为尚未验收 |
| libmediandk.so 完整性 | L2 | 共享maps精确过滤＋文件前两个可执行section基线＋CRC字节序/XOR＋内存比较；可表达非46的原终止条件 | 缺Android文件基线采集与MemoryReader集成；库未加载/未建立基线不能简单显示“被修改” |
| libc.so 完整性 | L2 | 同一比较核心；仅返回12时锁存libc位，进入event21第3项 | 不能覆盖库中全部内存、全部Hook类型，也没有官方可信文件基线 |
| libandroid.so 完整性 | L2 | 同一比较核心；仅12锁存，进入event21第2项 | 同上，且独立APK可能尚未加载该库，需要明确加载状态 |
| libart.so 完整性 | L2 | 同一比较核心；仅12锁存，进入event21第1项及event24的0/1 | 不能把这两个输出当作两种额外检测；不能把CRC差异直接归因于LSPosed |
| event22 / task35 类可见性 | L3（机制） | 输入显式类名单，按原FindClass查询，保序保重复；异常清除继续，非string终止列表；无效/空配置给空22，JNI失败0xBBA | 没有原真实类名单；FindClass受线程和ClassLoader影响。机制完整不等于“Xposed检测名单完整” |
| 无障碍 event25/33 / task38 | L3 | 真实枚举已启用服务ID，按原排序副本CRC生成首次/变化/不变结果，保留原序输出；可显示增删差异 | 没有KeyMapper专用匹配或联合处罚规则；服务存在不等于作弊 |
| 输入法 event34/35 / task40 | L3 | 真实getInputMethodList→getServiceName，首次34、变化35、相同None；保留原哈希及错误边界 | 不是默认输入法、不是仅已启用输入法，也没有证明KeyMapper交集规则 |
| MCP文件 event32 / task39 | L3 | 两遍本进程fd符号链接扫描，严格后缀/前缀、MCPK头、offset24最多64字节、basename:text、保序重复及空事件 | 不是全盘脚本搜索；未打开/不在可见fd中的文件不在扫描范围；独立APK看不到游戏自己的fd集合 |
| event20 / task33 匿名可执行映射计数 | L1 | 已有显式parsed entries下的A/B计数、size>0x5000、B-baseline16、失败时+24可能保留旧值的模型 | baseline16后续写入者、独立raw scanner畸形输入语义及原诊断文字未闭合；不能作为完整event20扫描器 |
| event19 设备身份派生 | L3（本地采集/派生） | Widevine原字节→大写hex→固定盐SHA256；失败回退boot_id；可显示来源、最终值与失败 | 本APK结果不保证与目标APK的应用作用域值相同；boot_id随启动变化；不是“设备是否已被封禁”查询 |
| event19 APK证书摘要 | L3（原行为，有强门槛） | sourceDir路径/文件大小判断、APK v2首个signer首张证书SHA256和FAIL_1..6 | 小于1GiB的普通调试APK会返回FAIL_5；不是完整APK签名认证、官方证书匹配或全APK摘要 |
| event19 包名/Activity特征 | L3 | 读取调用Context的包名和声明Activity列表，计算原wx前缀/mpay特征 | 不是当前前台Activity监控；独立APK观察自己的声明，不能冒充目标宿主 |
| AArch64入口指令自检 | L1（通用分类器） | 已有三条指令输入的B/BRK/BR模式函数，可用于明确地址的局部实验 | 尚无全库检查点/可达性清单、现场取指适配及对应原函数覆盖；合法跳板也可能匹配，非通用Hook鉴定 |
| 宿主门控0x41de58 | L1 | 可解释已见5486比较、Not NEMC/0x138B及部分环境线程启动分支 | 5486字段语义和全部门控不明；普通调试APK不能宣称忠实复现原启动条件 |
| 多时钟→RNG | L0（作为作弊检测）；支持代码可复用 | 已恢复clock ID回退、时间/PID/20字节熵、HMAC_DRBG，可作支持链观察 | 没有时间差阈值或变速判定证据；不能把它变成“变速检测”按钮 |
| Root/模拟器/Frida/KeyMapper专用规则 | L0 | 当前可显示相关已恢复采集事实；如后续新增规则需另标为自定义 | 不能称为本样本已挖出的专项检测 |
| task36 | L0（作为新增检测） | 已恢复正常路径返回kind1/None | 不存在因任务编号36就必然有event36的推论 |

四库的 L2 不是说其主要比较分支仍不明：最新过滤器/CRC/比较状态机已经具备明确实现，欠缺的是把现场文件、内存、加载状态和生命周期接成可检验的 Android 检测器。

来源：[新四链核心](../chain_closure_20261018/src/detection_chains.cpp)、[Android采集](../chain_closure_20261018/src/android_collectors.cpp)、[类JNI](../chain_closure_20261018/src/classes_jni.cpp)、[四库与IME核心](../environment_memory/src/environment_memory.cpp)、[IME JNI](../environment_memory/src/input_methods_jni.cpp)、[无障碍接口](../accessibility/src/accessibility_monitor.hpp)、[身份Android适配](../device_identity/src/android_adapter.cpp)、[MCP原生采集](../mcp_clock/src/mcp_chain.cpp)、[入口模式](../src/verified_helpers.cpp)、[任务映射](../coverage_audit_20261018/evidence/task-map.json)。

## 影响实现程度的细节

### 四库“正常”不等于实际完成摘要

compare_mappings的46存在两条路径：完成首个可读可执行候选的区段比对；或者候选非空但没有执行任何可执行区段比较。APK必须同时展示sections_compared、候选数、选择基址及完整性状态。

原基线最多选两个SHF_EXECINSTR section，不是全库哈希；基线来自现场文件，不自带官方签名信任。文件与内存一致只说明已比较范围一致。路径变化可先于权限检查触发原终止分支。

目前MemoryReader是注入式函数接口，没有现成完整的Android现场实现。直接memcpy任意地址不能作为可靠集成：应处理映射变化、读取失败和可能的不可读区段。这个适配工作不需要重新发明CRC规则，但必须在设备验收。

libc/libart通常已由应用运行环境映射，libandroid/libmediandk不应假定总已加载。是否主动加载会改变被观察环境，报告要记录加载前后。原循环的初始100及每100轮扫描是轮数，不是100秒；不能擅自声称恢复了原定时周期。

### 类探测的机制与实际名单是两件事

外部请求明文形状为[35,[类名…]]，当前能忠实处理给定名单。没有固定内置名单可从该SO推出。

JniClassBackend直接FindClass；已附加Java线程、native附加线程和不同ClassLoader的结果可能不同。APK若为了“查得更多”另加自定义ClassLoader遍历，就增加了新的检测行为，应保留原FindClass结果作为基准。空名单查询数为0，应显示“未配置”，不能显示“未发现Xposed”。

### 采集状态与原判定需同时保留

这些已有行为不能丢失：

- TracerPid的-2/-1不触发原阳性分支，但表示采集/字段问题。
- Seccomp缺字段与读失败不同；mode、NNP的值不能代替原聚合规则。
- SIGSYS查询失败不一定使原acceptable=false；必须显示handler.error。
- 未做必要的主动probe是未完成。恢复失败可能仍有原布尔结果，但进程信号状态没有正常回滚。
- MCP的Scan.complete()只约束indeterminate_files，不自动代表两次目录都成功打开；应同时检查first_directory_open/second_directory_open。
- 无障碍/IME的部分列表不能当完整快照投入变化检测。
- event20失败后的empty24可能是上次值，应标注陈旧状态。
- 原本地终止在重建中是local_termination观察字段，调试界面可以展示“原逻辑会终止”，而不会因此失去全部诊断数据。

建议每次结果至少含：检测项、PID/进程名、采集时间、输入/配置来源、原返回码/事件、采集成功/未完成/失败、实际比较/查询数量、原本地终止条件、证据入口。此结构属于调试工程设计，不冒充原网络协议。

### 证书字段的1GiB门槛

[Android适配第110行](../device_identity/src/android_adapter.cpp:110)明确保留文件size<0x40000000→FAIL_5。本轮IDA Pro MCP重新检查0x37843c，与保存的合成stat实验及重建方向一致。

因此“原行为复现”模式中，小调试APK得到FAIL_5是预期分支，不能据此判实现坏了。若希望另外显示小APK证书，可独立调用已有first_v2_certificate核心或增加系统API采集；这属于附加诊断，不能替换后再宣称原行为完全一致。已有核心是v2证书提取，不是Android平台完整签名验证器。

### 事件传输不应阻塞本地调试，但不能标成完成

event19已保存有界原指令fixture：事件→JSON→AES-GCM→单槽type5输出ring。其会话密钥为显式输入，type8完整握手和多槽writer尚未闭合；其他事件未逐项完成同等的端到端回放。

本地APK可直接展示结构化结果，无需先恢复宿主网络。若要求“与原服务器互通”或“预测封禁”，现有证据不足。HMAC/AES、ring、RNG均是支持组件，不应计作额外作弊检测。

## 当前工程资产核对

现有代码是多个独立语义模型和JNI/平台适配器，尚无AndroidManifest.xml、Gradle app工程或Java/Kotlin界面，也未发现连接这些模块的Java_*入口/JNI_OnLoad/RegisterNatives应用桥。

特别需要修正构建计划的输入基线：

1. [聚合CMake](../aggregate/CMakeLists.txt:59)仍只列旧17个翻译单元。
2. [聚合脚本](../scripts/build_all_detections.ps1:83)同样未列入10月18日新增detection_chains.cpp、android_collectors.cpp、classes_jni.cpp。
3. [打包白名单](../scripts/package_source.ps1:26)未包含chain_closure_20261018；实际ZIP中也没有上述文件及最新四链报告。
4. 最新四链有自己的libprism_chains.so与测试程序，但它不是完整APK，也不等于已并入聚合库。

后续APK应从当前工作区专项源码整合，复用公共依赖一次；仅取dist的旧ZIP或旧聚合SO会漏掉关键新增能力。本轮只指出差异，没有改写构建脚本或重打包。

## 已有验证与本轮核验

| 保存记录 | 可支持的结论 | 不能支持的结论 |
| --- | --- | --- |
| 四链112核心＋10 JNI mock | 重建边界/状态机和JNI表适配场景通过 | 原件全链差分、Android现场通过 |
| 旧seccomp 704、类探测404 | 已模拟依赖下的原控制流/包装吻合 | 704/404次真机检出、真实类名单完备 |
| 四库/IME73＋JNI8，摘要6/IME哈希9保存结果 | 核心比较/指纹及mock适配已有支持 | 现场MemoryReader、所有Android版本兼容 |
| 无障碍保存原哈希42、消费者180、JNI/env等 | 指纹/事件及有界JNI行为支持较强 | 真实调度和服务端规则 |
| 设备身份117项 | 独立密码oracle、保存原件fixture及单槽链支持 | 完整会话、真机身份稳定性和多槽等价 |
| MCP/时钟46＋98独立对照 | 已重建文件/随机数语义及密码实现 | 原SO或Android现场等价 |

以上测试本轮均未重跑。已有Android记录均为交叉编译；不是安装运行结果。

本轮额外完成的只读核验：

- 原SO SHA256匹配92e7d4adda7e222aa9dce389009a186adabb2602b80d618d417e0f6d509adaf4。
- 四链manifest选取的6个源码/头文件＋1个SO共7/7匹配，复用的6个依赖6/6匹配。
- 旧聚合manifest的17个输入翻译单元＋SO共18/18匹配；说明旧聚合产物未漂移，不说明已包含新四链。
- IDA Pro MCP只读抽查0x37843c、0x47fafc、0x6ab3d8；返回存在混淆/反编译限制，作为现有汇编及fixture结论的交叉核对，未新建函数或patch样本。记录见[ida-spot-check.json](ida-spot-check.json)。
- 本轮查看的交付IDB快照检查前后SHA256一致：54aafe7dfe2607b63f5de896db5cb7b0f38c5da30409b395692e5415ba377017；查看worker及本轮临时工作文件已清理。
- 历史environment-memory IDB在上一轮发生哈希变化的问题仍按原[verification.json](../chain_closure_20261018/evidence/verification.json)保留。该文件明确code_and_build_checks_passed=true、protected_file_check_passed=false、passed=false，不能写“上一轮全部通过”。

本轮核验明细见[verification.json](verification.json)。来源会话为[codex://threads/01a14a95-b775-7f90-a3c4-59d631293e34](codex://threads/01a14a95-b775-7f90-a3c4-59d631293e34)。

## 未来构建后的验收条件（本轮未执行）

| 项目 | 最小有意义的设备验收 |
| --- | --- |
| TracerPid | 无ptrace附加与native调试附加对照；比对本进程原始status、返回码、线程上下文 |
| Seccomp/SIGSYS | 保存status/action/maps/path/layer；在可控测试进程验证inactive、映射来源、probe触发/未触发及handler恢复；异常采集不能折成绿色通过 |
| 四库 | 匹配同版本真实文件/内存，记录section和实际比较数；在自有测试库验证内容差异与路径变化，再核对四库运行条件 |
| event22 | 同一名单在Java进入native线程及native附加线程比较；含可见/不可见/异常/重复及非string截断；记录ClassLoader上下文 |
| 无障碍/IME | 首次、相同、增删、重排与空列表；确认API返回列表类型；JNI失败不改首次/上次哈希 |
| MCP | 自有测试文件保持fd打开，匹配/不匹配后缀、重复fd、offset24文本、短读/EOF/目录失败；关闭fd后重新扫描 |
| 设备身份 | Widevine成功、禁用/失败回退、boot_id读取失败及重启变化；不预设跨应用相同 |
| APK属性 | 小APK走FAIL_5；独立核心用已知v2证书fixture比对；包名/Activity取调用Context |
| event20 | 先补独立reader和baseline16证据；当前只接受显式输入的模型回放，不能用真机截图宣称全链完成 |
| 入口/宿主门控 | 先补目标地址清单/取指和5486语义；可先展示片段，不设综合“环境安全”结论 |

## 下一步建议

若后续目标是“调试已挖出的检查，观察它们实际看见什么”，可以进入APK设计：先接L3项目；四库作为明确的L2集成工作；event20、入口自检和宿主门控标记实验性/待补证。保留原语义结果与额外诊断状态。

如果目标是“证明原游戏一定不会检出”或“完整还原Prism全部检测”，当前还不能据此立项为已完成能力；需要同进程输入、原配置、启动/调度与外部链证据。这里缺少的是可验证条件，不宜用一个总百分比掩盖。

## BEFORE / AFTER / ROLLBACK

BEFORE：现有源码、证据、聚合SO与ZIP保持原状，最新四链单独交付。

AFTER：仅新增本评估目录的报告和IDA只读抽查记录/核验摘要；未构建、安装或部署，未改检测源码或原样本。

ROLLBACK：删除本评估目录即可撤销新增报告；本轮查看的交付快照前后哈希匹配。历史IDB异常的恢复边界沿用原报告，不在本次评估中声称修复。

