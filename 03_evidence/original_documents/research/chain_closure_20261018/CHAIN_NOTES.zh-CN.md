# 四条检测链静态收口记录

本轮：2026-10-18，单线程 IDA Pro MCP，研究数据库 `prism-chain-closure.i64`，image base 0。未执行原 ELF，未 patch 字节。地址均为本样本地址，不能当作其他版本偏移。本文先于 C++ 重建落盘。

## TracerPid

`0x40fd54 → 0x406068`。`0x5fe6c4 → 0x5feca8/0x5fea58` 构造 `/proc/<getpid>/status`，不是其他进程的 status。路径静态解码见 `evidence/string-static-decode.json`，旧 `/status`、`TracerPid:` 见 `../evidence/stage2_strings.json`。

- `0x406178` openat(-100,path,0,0)，失败 `0x406198` 返回 -2。
- 栈分配 2048 字节；`0x4065dc` 零填充值、`0x4065e4` 结束地址，逐字节清零。`0x406a00` 只读一次，最多2047，随后 close；read<=0 返回 -2。最后一个零字节由预清零保证。
- 从整个 C 字符串查找首个 `TracerPid:`，不是按行首匹配。内联搜索首字节后比较余串，没有要求前一个字节是换行；`0x408aa8` 保存匹配指针，空返回-1。
- 加 marker 长度，跳 tab/space，再进入 atoi 风格解析；跳 ASCII space、9..13，允许一次 +/-，无数字=0。`0x4090c0` 初始化累积0，`0x40928c..0x4092b0` W寄存器负累积 `acc*10-digit`，不检查溢出。最终按符号返回，保留32位回绕。
- `0x4106f8/0x4106fc` 有符号 >0 才触发终止。-2、-1、0、负数均不触发该分支。
- `0x4497e0 → 0x4c3778`：getpid/gettid（gettid==-1回退pid）、tgkill(9)、exit_group(2)、BRK。终止为本地效果，不是服务端处罚证据。
- 每次成功普通环境循环均检查 TracerPid，四库检查才受100轮计数门控。还有10轮辅助诊断及线程休眠，不将轮数解释成秒。

## seccomp / SIGSYS

状态采集 `0x464d9c`：12字节数据初始两个int=-1、布尔=false。读取同进程status，4096字节清零、一次read最多4095、close。open失败诊断0xfa1，read<=0诊断0xfa2。正数读取后解析 `Seccomp:`、`Seccomp_filters:`、`NoNewPrivs:`。`0x468a48` 全文子串搜索，缺字段返回-1；匹配后跳冒号、tab、space，再经 `0x4bab9c → 0x4ba308` atoi；NoNewPrivs严格等于1才为true。

成功数据为 mode(+0)、filters(+4)、nnp(+8)。`0x47e398 → 0x4b64a4 → 0x4b66c8 → 0x4b6aac → 0x4a6c7c` 检查 variant 的 +12 index==1（错误alternative）；不是用mode==1判异常。单纯缺字段不等于采集错误。聚合器只消费filters；mode/nnp采集到但不用于此处最终布尔。

`0x46dc28` direct rt_sigaction(SIGSYS=31,null,&old,8)。失败为0x1389；handler指针为0或1时 inactive，其他值 active，**不以SA_SIGINFO位判断active**。active时调用 `0x5cc630("",true)`，取第一个 `start <= handler < end` 的映射，记录路径与区间，不检查rwx。无匹配则保持空路径。

`0x471c8c(handler_info, filters, layer)` 原因码：

| 条件 | reason | 分类器 `<10` |
|---|---:|---|
| inactive | 0 | 接受 |
| active，来源路径空 | 11 | 不接受 |
| 路径不以 `/data/` 开头 | 2 | 接受 |
| `/data/` 内，不属于以下三种前缀 | 12 | 不接受 |
| 可接受前缀，filters>=0且<=int32(layer+1) | 3 | 接受 |
| 数量不满足，主动探测标记改变 | 10 | 不接受 |
| 数量不满足，主动探测返回false | 4 | 接受 |

三种前缀是 `/data/app/`、`/data/data/`+cmdline+`/`、`/data/user/0/`+cmdline+`/`。cmdline来自 `0x4778bc`，read最多255，取首个NUL前；未去掉`:子进程`。前缀比较为字节strncmp。producer中调用 `0x47a44c` 后没有使用返回值作决定；不能额外加入包名相等要求。

主动探测 `0x47cc00`：

1. `0x5cc630("/base.apk",true)` 顺序候选，要求路径 `/data/app/` 前缀。
2. 当前cmdline非空时，`0x47a44c` 提取安装路径包名，必须与cmdline相等；cmdline空时无需相等。取首个合格项，否则 `/dev/null`。
3. 包名提取：`/data/app/`后若是`~~`则越过一段到下一个`/`；从当前段开始取首个`-`之前，缺少必要分隔符/空名字返回空。

   最后一次复核确认 `0x47b718` 是从当前位置查找字符45，没有以`/`限定查找终点。因此畸形输入 `/data/app/pkg/dir-x/base.apk` 会提取 `pkg/dir`，不能在重建中额外加路径规范化。
4. marker=`0x6ab22396`；临时handler=`0x496f38`、flags=4、空mask；rt_sigaction(31,new,old,8)失败直接false。
5. openat(-100,path,0,0)；比较marker是否变化；fd>=0时close；恢复old handler；返回比较结果。没有安装seccomp filter，也没有prctl。恢复失败没有改变原返回值。
6. handler仅在siginfo非空、si_code==1、si_syscall==56时将marker改为`0x6ab22397`；任何非空ucontext均写`+0xb8=-1`，并非仅匹配时写。NDK AArch64布局对应uc_mcontext.regs[0]，重建交叉编译用static_assert核对。

聚合 `0x47df58` 保留旧模型：status错误置status_failed；filters有符号超过int32(layer+1)置excessive；handler采集失败不直接置suspicious；成功原因>=10才置suspicious并复制来源路径。+40第二字符串只初始化为空，此函数没有写入用途。上层 `0x47fafc(layer=0) → 0x2aacd4` 将异常字段拼诊断，提交5006；此位置未见独立终止或固定事件号。

真实主动探测是进程级临时信号状态变更，没有观察到互斥保护；模型保留install/open/close/restore顺序，平台执行另置接口。未探测必须标记未完成，不能当false。

## maps 与四库完整性

`0x5cc630` 共享读取器：open失败空vector，fdopen("r")，getline逐行。没有fdopen结果空值检查，直接交给getline。重建将此原件未定义/崩溃边界显式标为incomplete，不能当正常空列表。

过滤器 `0x5fb6ac → 0x5f917c`、`0x5fdbe0 → 0x5fb6b0` 为相同strstr形状：先保护空指针，needle首字节为空返回haystack；非空needle顺序扫描首字节，再按余串长度比较。过滤整行：必须含requested_name；exclude低位为1时排除含`(deleted)`。无rwx过滤。路径/子串都按C字符串边界。

空needle分支已按汇编复核：`0x5fa72c/0x5fa738`分别保存X0 haystack与X1 needle；`0x5fa8a0`读needle首字节，`0x5fabc4..0x5fabdc`在零字节时选择state `0x9da6229c`，经`0x5fa9dc`进入`0x2c413d45`，`0x5f94ac..0x5f94b4`复制尚未前进的haystack指针到返回槽。不能使用Hex-Rays显示成同一savedregs槽的错误栈别名判断此分支。

命中过滤后无条件 `line[getline_len-1]=0`，因此没有换行的最后一行会丢最后一字节。sscanf格式静态解出为 `%lx-%lx %4s %lx %x:%x %lu %n%*s`，必须返回7。起止、offset、dev、inode从原行提取；%n后再跳空白，保留完整剩余pathname，包括内部空格。r/w/x按1/2/4置位，第四字符p为private；不额外验证start<end。结果保持原序。

已有基线/CRC/比较器复用 `../environment_memory/REPORT.zh-CN.md` 与源码：

- `0x449dd0` ELF64 section headers，最多前两个SHF_EXECINSTR section；不是PT_LOAD。
- `0x44c740` Botan CRC32，摘要BE字节按LE u32读再xor mask；已有专项原指令证据，不重复执行。
- `0x44d0b8`：未初始化23；空候选57；路径变化在权限判断前终止并返回12；不可读跳过；可读非执行保存fallback+56；首个可读可执行映射选择同一base比较所有section。section超map.end且存在fallback则消费一次fallback。mismatch12、match46；非空但没有可执行映射也可46。
- `0x40fd54` 初始counter=100，unsigned>=100做media/libc/android/art一批；media!=46本地终止；其他库仅12锁存且锁存后跳过。成功批次counter=0，再做每轮TracerPid。event21顺序art/android/libc；event24读取art。

event20是另一条读取链 `0x650898 → 0x3b3860`，不能沿用“返回过滤后的maps路径集合”旧说法。它malloc0x20000，循环read直到<=0或累计0x1ffff；有部分数据后即使后一次read失败也解析已有部分。补NUL，按换行分割，末行无换行仍解析。可执行、size>0x5000且path为空计A；非空且含`/dev/zero (deleted)`或以`[anon:`开头计B。正常路径未向返回vector追加普通路径；只见open/malloc/无数据失败写诊断字符串。正常返回数组为计数前两项，错误可附诊断。

event20初始清state+20，正常结束写+20=B-state+16（32位回绕）、+24=A；失败保留+24旧值。`0x3d764c`构造state+16=0；本轮全地址ADD #16查询未确认后续写入者，不能保证全生命周期固定为0。此字段重建保留显式输入，作为event20额外分支的剩余数据来源边界，不影响四库比较的闭合结论。

## event22 配置与结果

`0x4c89cc → 0x4cb88c` 输入消息分派；type3分支 `0x593864` 经会话解包后 `0x2a7648` JSON parse，要求外层array至少2项，item0 number、item1 array。item0的cJSON valueint(+0x28)低字节进入request+0；item1由`0x2a8498`脱离原JSON并持有在request+8。

`0x58c5b0` 经`0x596e90`取ID、`0x597284`取配置；`0x58cd1c`查询registry、实例化/取得任务，`0x58f774 → 0x4ec864`只借用JSON指针，虚表+64同步调用任务。ID35对应vptr0x793d48、执行0x6ab3d8。故该路径的明文结构是 `[35,["CLASS_A",...]]`；多余外层项未作为该配置读取。真实名单由外部请求提供，静态样本不能补出实际运行名单。

注册与工厂进一步串接：旧审计的`.init_array`入口`0x6948bc → 0x6943dc`在`0x694624`传ID35；`0x694c84`取`0x4ea8b8` registry，构造工厂后在`0x694d10`调用共同注册器`0x601c58`。工厂构造为`0x6b6660 → 0x694e5c → 0x6951fc`，后者`0x69544c → 0x695a3c → 0x6971b8`写入工厂vptr `0x793d00`。该虚表+0x30为`0x698f10`，调用`0x6a7cf4 → 0x6a8154 → 0x6a893c → 0x6a94a0 → 0x6a9794`，分配8字节checker，经`0x6a9bcc`写入vptr`0x793d48`。checker的ID槽+0x18返回35，执行槽+0x40为`0x6ab3d8`。此段为静态构造/引用证据，未执行注册或调度回放；不增加隐藏类名单结论。

`0x6ae288`要求配置指针非空、type低字节32（array）、child count>0。无效/空配置直接构造空event22，不获取JNI。有效非空配置先经`0x306df0`获取当前线程JNI环境；失败诊断0xbba，无event22。线程获取/attach/detach复用已验证accessibility_env。

循环条件为node存在且type低字节16（string）；遇非string终止整个列表。对每项原字符串FindClass；ExceptionCheck非0则Clear并继续；无异常且class非空才DeleteLocalRef并复制原字符串入输出。保序、保留重复、没有点斜线转换；内嵌NUL以首NUL为界。valuestring空指针是原件未保护边界，重建拒绝并标incomplete。没有显式自定义ClassLoader加载；可见性由当前JNI线程/VM上下文决定。

成功结果22进入 `0x51e9c4` 的既有Event转换/加密路径，再由 `0x56b96c → 0x4ce0f4 → 0x591b70 → 0x58fac8` 写输出ring；Error走type6，Event走type5。此处为静态通路串接，未新增event22全链原指令执行或真机验证，宿主网络/服务端用途仍外部未知。

## 重建边界

以上四条核心检测链已可写为确定的输入→分支→结果语义；真实status/maps/handler/类名单是运行输入，不应凭样本猜值。保留未完成/失败/阴性区别。通用混淆器的函数入口自检、C++异常/OOM/并发与真实宿主网络不冒充已等价重建。event20的state+16后续来源和原始诊断文字另列剩余项。
