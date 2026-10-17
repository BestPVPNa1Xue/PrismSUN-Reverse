> 归档阅读副本：只调整文件超链接；原文、代码块中的历史路径与结论保持原样。[逐字节原始文件](../../../03_evidence/original_documents/research/chain_closure_20261018/REPORT.zh-CN.md)。历史失效链接转到文件索引，原目标见 `00_guide/report-link-audit.json`。

# TracerPid / seccomp / maps完整性 / event22 收口与C++重建

日期：2026-10-18。目标样本：`D:/PrismSUN/libprism-sun.so`，AArch64，image base 0，SHA-256 `92e7d4adda7e222aa9dce389009a186adabb2602b80d618d417e0f6d509adaf4`。

## 本轮交付结论

四条指定主链的采集边界、主要判定分支、失败语义及本地消费者现已能形成确定的C++语义实现。补齐了此前最关键的未知：TracerPid读取与整数规则、seccomp原因码生产者/主动SIGSYS探测、四库共享maps过滤器、event22配置输入与有类型列表遍历。具体地址与分支依据见[静态笔记](CHAIN_NOTES.zh-CN.md)。

这里的“收口”指本样本的检测语义。没有把全库通用入口保护、整个消息握手/多槽writer、真实宿主/服务端以及其他检测模块宣称为全量等价；也没有从FindClass推导一个固定Xposed名单。

| 主链 | 本轮确定的输入与行为 | 消费者/输出 |
|---|---|---|
| TracerPid | 本进程status，一次read<=2047；全文首个marker；失败-2、缺marker-1；atoi式32位回绕 | 每个普通环境循环检查signed >0；阳性本地tgkill/exit_group；四库100轮门控不控制此检查 |
| seccomp/SIGSYS | status一次read<=4095；variant错误与字段缺失不同；handler 0/1 inactive；其余用首个半开maps区间定位；reason 0/2/3/4/10/11/12 | 采集错误、数量超限、可疑来源是不同标志；layer0异常提交诊断5006；未证实此处独立终止或服务端裁决 |
| maps/四库 | 整行strstr过滤、deleted排除、无条件删除末字节、sscanf七字段；复用已验证ELF section/CRC比较器 | 23/57/12/46；路径变化先于权限检查；media非46终止，其余仅12锁存；event21与event24沿用原模型 |
| event22 | type3请求解包JSON `[35,[类名…]]`；第二项借给任务35；FindClass按原字符串；非string截断、异常清除、保序保留重复 | 无效/空配置输出空22；有效非空但JNI失败为0xbba且无22；成功经既有Event/type5输出ring链，Error为type6 |

SIGSYS主动探测没有安装seccomp filter。它临时安装SA_SIGINFO handler，对选出的本进程base.apk或`/dev/null`调用openat，根据marker是否变化判定，再尝试恢复旧handler。恢复失败不改变原布尔返回。任何非空ucontext都被写入x0=-1，marker变化才要求si_code==1、si_syscall==56。重建暴露恢复结果，不将未探测伪装为阴性。

## 代码落地

新增代码位于[src](../../../01_source/research/chain_closure_20261018/src/detection_chains.hpp)：

- [detection_chains.cpp](../../../01_source/research/chain_closure_20261018/src/detection_chains.cpp)：Tracer/status/有边界的maps解析、SIGSYS定位与原因码、可测试probe状态机、四库比较组合、typed event22及request视图。
- [classes_jni.cpp](../../../01_source/research/chain_closure_20261018/src/classes_jni.cpp)：真实JNI FindClass/ExceptionCheck/Clear/DeleteLocalRef适配；复用既有`ScopedJniEnvironment`，仅本scope附加的线程才Detach。
- [android_collectors.cpp](../../../01_source/research/chain_closure_20261018/src/android_collectors.cpp)：Android ARM64直接syscall采集器与临时SIGSYS probe backend；status/cmdline一次读取，maps fdopen/getline；编译期核验NDK siginfo/ucontext布局。

复用依赖：`../environment_memory/src/environment_memory.{hpp,cpp}`、`../src/observed_models.{h,cpp}`、`../accessibility/src/accessibility_env.{hpp,cpp}`。这些旧源码未改写；新入口增加精确maps过滤流程，旧的宽松maps解析辅助函数不再作为这四条新链的解析入口。

提供的是C++17语义重建，不复刻原C++对象ABI。JSON文本解析与会话密码处理仍是既有输入适配边界：`JsonValue`表达cJSON的type低字节、valueint、nullable valuestring及有序children，`request_view`借用第二项而不复制底层cJSON ownership。此轮没有增加APK工程、UI或安装脚本。

真实Android采集器不包含自动启动线程，也不会在SO加载时安装handler。`inspect_seccomp(layer, false)`只采集；当原逻辑需要主动probe时返回`complete=false`。显式传true才调用probe。该probe改变进程级SIGSYS action，调用方需保证独占执行；原件未发现锁。恢复失败可从`ProbeResult.restore_succeeded`观察。JNI adapter必须在同一线程构造、使用、销毁。

本地终止在模型中为`local_termination`观察值，不实际杀死调试APK；终止链的syscall及参数已记录在静态笔记。原件未保护的fdopen失败/null valuestring在重建中显式标为incomplete，未复制崩溃。整数sscanf重建限定在可表示的Linux maps字段；非法数值溢出、C++异常/OOM、并发信号和真实ClassLoader差异不宣称与原件等价。

## 验证结果与边界

实际运行本轮[构建脚本](../../../01_source/research/chain_closure_20261018/scripts/build.ps1)：

- Windows宿主核心112项检查全部通过，覆盖读取上限/NUL/符号回绕、maps末行/整行匹配/半开区间、七种reason与layer回绕、probe顺序及恢复失败、四库组合与逐轮Tracer、typed配置/JNI错误、event20计数消费边界。
- JNI/VM函数表mock10项检查全部通过，覆盖已附加/需附加/附加失败/版本错误/null VM、异常与引用释放、非string截断、无效输入下Detach。
- Android ARM64/API24共享库和两份测试程序交叉编译成功，`-Wall -Wextra -Werror`及`--no-undefined`通过。
- NDK静态断言确认SIGSYS=31、SA_SIGINFO=4、openat=56、rt_sigaction=134、si_code偏移8、si_syscall偏移24、uc_mcontext.regs[0]偏移0xb8；JNI四个槽偏移也通过。

证据：[host-tests.json](../../../03_evidence/research/chain_closure_20261018/evidence/host-tests.json)、[jni-tests.json](../../../03_evidence/research/chain_closure_20261018/evidence/jni-tests.json)、[build.json](../../../03_evidence/research/chain_closure_20261018/evidence/build.json)、[verification.json](../../../03_evidence/research/chain_closure_20261018/evidence/verification.json)。第一次编译因测试lambda的误导缩进被`-Werror`拦截，已拆成两行；没有放宽编译参数。112/10是重建测试，不是原件差分次数；既有704/404及四库摘要专项结果只作历史支持，本轮未重跑。

本轮未运行原SO、未仿真原指令、未运行Android产物，也未采集真实宿主或网络。Android内存可读性、设备权限、OS版本、运行时handler和ClassLoader可见性仍需后续设备验证。

## maps扩查的event20剩余项

event20属于独立reader，不能冒充四库共享parser。此次确定它使用malloc0x20000后循环读取至0x1ffff，部分读后再失败仍解析已读数据，末行无换行仍处理；可执行且size>0x5000，空路径计A，`/dev/zero (deleted)`子串或`[anon:`前缀计B。输出数值是B-state+16与A。失败清+20但可能保留+24。正常路径未见追加普通maps路径，错误路径才附诊断字符串。

仍未闭合三项：state+16构造后其他写入者、原始错误诊断文字、独立混淆raw数字scanner全部畸形输入语义。已定义指令的ADD #16扫描无确认结果，不能将其当作穷尽证明。`event20_counts`仅重建已经确定的计数消费，以parsed entries和baseline16作为显式输入；没有标为完整event20检测器。这些缺口不在四库比较器中，但后续若要声称“所有maps相关检测都完整”，必须继续解决。

event22真实类名单、status/maps瞬时值和handler地址属于外部运行输入，不能靠静态样本补造。宿主门控`0x41de58`、全库入口自检覆盖和其余注册/调度任务仍属于原覆盖审计的后续范围；本轮没有据此排除其他独立大检测点。

## 数据库与回滚

全程单线程、IDA Pro MCP与本地证据，无REA、无子代理。当前数据库副本[prism-chain-closure.i64](https://github.com/BestPVPNa1Xue/PrismSUN-Reverse/releases/download/research-2026-10-18-r1/PrismSUN-research-20261018-r1.zip)已保存；另保留未被IDA打开的[交付快照](https://github.com/BestPVPNa1Xue/PrismSUN-Reverse/releases/download/research-2026-10-18-r1/PrismSUN-research-20261018-r1.zip)，manifest对快照计哈希，活动IDB及工作文件不作为不可变产物。FDE辅助恢复函数边界和被误标成数据的指令定义，未patch样本指令字节。`auto_analysis_ready=false`仍然存在，不能将本轮已确认分支扩展成全库自动分析完毕。

BEFORE：[protected-before.json](../../../03_evidence/research/chain_closure_20261018/evidence/protected-before.json)保护原SO、原IDB及三份历史研究IDB；`evidence/PROGRESS.before.md`保存本轮最终更新前进度文件。

AFTER：[protected-after.json](../../../03_evidence/research/chain_closure_20261018/evidence/protected-after.json)核验4/5不变：原SO、原IDB、prism-analysis及coverage-audit均匹配。**历史prism-environment-memory.i64哈希变化**，大小仍80890951：before `2e5d5d376645dc2639c4831e81c4aef69f1bf28ba1426ac6f8ef1753198d74cb`，after `9b42703d07151e07bcc1a8346885cb900975637332a83e3afd985021375abf20`。该历史库曾在本轮开始由独立worker dcf52c30打开；快照时间00:32:27，文件修改时间00:43:04，worker PID18204已退出。插件闲置退出会调用close_database，时间线与此相符，但未保留可逐字节比较的before副本，**不能认定仅元数据变化**。见[会话证据](../../../03_evidence/research/chain_closure_20261018/evidence/historical-idb-session.json)。没有回写历史库以强行匹配旧哈希；最终verification明确将保护文件检查标为失败，代码/构建检查另记通过。[manifest.json](../../../03_evidence/research/chain_closure_20261018/manifest.json)记录本轮源码、产物、文档、证据及旧源码依赖SHA-256。原始SO补丁偏移/字节：无。

ROLLBACK：返回未修改的旧`environment_memory`源码即可；本轮目录为独立新增。要撤销进度条目，恢复`evidence/PROGRESS.before.md`到`../PROGRESS.md`。新IDB打开时勿直接删除其工作文件；可保留本轮目录作为证据，无需对原SO执行还原操作。历史environment-memory库没有保留匹配before哈希的完整备份，无法声称可精确回滚该库；其他保护库可按其原用途继续使用。

对该历史库还做了只读有界核验：在内存中枚举文件头前128字节的1024种单bit变化，均不能复现before SHA-256，见[文件头核验](../../../03_evidence/research/chain_closure_20261018/evidence/historical-idb-header-check.json)。这只排除了该有限假设，不证明差异位于其他区域或涉及分析内容；没有改写保护文件。
