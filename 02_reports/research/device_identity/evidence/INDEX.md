> 归档阅读副本：只调整文件超链接；原文、代码块中的历史路径与结论保持原样。[逐字节原始文件](../../../../03_evidence/original_documents/research/device_identity/evidence/INDEX.md)。历史失效链接转到文件索引，原目标见 `00_guide/report-link-audit.json`。

# 设备身份证据索引与 finding ledger

目标 SHA-256：`92e7d4adda7e222aa9dce389009a186adabb2602b80d618d417e0f6d509adaf4`。所有地址均为本样本 imagebase 0 下的虚拟地址。本文的“已回答”只覆盖表中边界；完整解释见上一级 `REPORT.zh-CN.md`。

| 问题 / Finding | 状态 | 原件入口 | 主要证据 | 限制 |
| --- | --- | --- | --- | --- |
| F01：Widevine 大写 hex 后加盐 SHA256 | Answered | 0x5a7be4、0x5ae1d4、0x4df3c8、0x5b9df4 | `collectors-original.json`、`digests-original.json` 中 SHA 部分、`asm-0x5ae1d4.txt`、REA dossier | MediaDrm 返回值为合成平台输入 |
| F02：boot_id 读取、NUL/CRLF 处理和同盐摘要 | Answered | 0x4dfc3c、0x5d8330 | `collectors-original.json`、`asm-0x5d8330.txt` | 文件 I/O 返回值被建模；无真机稳定性实验 |
| F03：ClientPropsChecker task 17 / event 19 | Answered | 0x6fe530、0x70294c、0x7153a8 | `registration-original.json`、`event-original.json` | registry insert/lookup 边界模型 |
| F04：输入数组/字符串校验、错误顺序 | Answered | 0x7153a8 | `event-boundaries-original.json`、`event-original.json` | C++ API 输入类型化；不是任意 JSON parser |
| F05：HMAC key 为运行时 byte vector | Answered | 0x5ba370、0x71ab84 | `hmac-original.json`、`session-original.json` | 握手 key 来源仅局部静态链路 |
| F06：Activity 声明特征 | Answered | 0x37fb88 | `activity-original.json`、`asm-0x37fb88.txt` | JNI 表/返回数据合成 |
| F07：APK v2 首证书 SHA256、最低 1GiB 门槛 | Answered | 0x37843c、0x4c0718、0x3780ec | `apk-wrapper-original.json`、`apk-original.json`、对应 asm | 合成 APK/合成 stat；没有真实宿主 APK |
| F08：会话安装、generation/sequence 布局 | Partial | 0x5b77d8、0x4d92b4、0x4d1f14、0x596b58 | `session-original.json`、`asm-0x56eae4.txt` | 安装器/getter 已验证，type8 完整握手未重建 |
| F09：紧凑 JSON、AES256-GCM framing | Answered | 0x596028、0x5bcdd8 | `packet-original.json`、`pipeline-original.json` | 固定合成 nibble/密钥；没有恢复原熵源 |
| F10：type5 单槽写入输出共享区 | Answered（所测场景） | 0x51e9c4、0x591b70、0x58fac8 | `pipeline-original.json`、`output-ring.bin`、`ring-original.json` | 分阶段串接原函数；并非整个宿主运行 |
| F11：多槽成功写入异常 | Partial | 0x58fac8、literal 0x3dc58 | `ring-original.json`、`ring-3.bin`、`ring-4.bin`、`xrefs_to-0x3dc58.json` | 未证明常量的运行时处理；C++ 是协议工程模型 |
| F12：宿主上传和服务器设备封禁 | Unknown | SO 边界外 | `rea-final-evidence.json` | 需要匹配宿主 APK/捕获/服务端证据 |
| F13：Widevine ID 的跨环境持久性 | Unknown | 系统 MediaDrm 边界 | 采集代码只能证明所请求属性 | 无真机、多版本、多应用实验 |

## 成功 REA dossier

全部保存在 `rea-evidence.json`，属于静态分析，不是运行捕获：

- `0x4df3c8`：`ev_87d6004c70c4f839302e89671e070505bd093bf65d64e31b0fd27a880e0d230d`。
- `0x5b9df4`：`ev_4b56a0c430a3a1ae51898e13a35065b4432f446c710589bfb42eebcc6ac79322`。
- `0x7153a8`：`ev_a83b9fd8e38ae9c3e93ec5fa4063d070699e5dd245b4aa9051f30f712c36fe51`。

`rea-final-evidence.json` 中 open unknown：`unk_2b3f4af1de30205ec5be0c8745d1dfdfdac2039cafc5d96caeda8feaac05a15f`。其 mutation `ev_ca2beff3f536e2f986d9f2c4d1fdad61ec149eedbc278ac608046fcf46716900` 只记录分析意图。REA session 已关闭。

## 记录格式与有效性

- `asm-0x*.txt/.json`：原 ELF 按 FDE 边界的 ARM64 汇编，JSON 含范围/FDE；优先于错误伪代码。
- `../decompiled/0x*.c/.json`：IDA 原始伪代码和完整响应。bad-SP/JUMPOUT 不视作已恢复完整语义。
- `xrefs_to-0x*.json`：IDA xrefs 响应；需结合范围和 provider 限制解释。
- `*-original.json`：原指令 fixture 输入/输出；`reason=returned` 是仿真返回，不代表 Android 真机运行。
- `constants-original.json`：原件字符串 writer/decoder 的合成执行结果。
- `ida-annotations.json`：17 个命名及 5 处说明注释；`ida-health-latest.json` 明示全局分析未就绪。
- `ida-restored-definitions.json` 与 `define-*`：数据库定义请求记录，包含已存在/失败，不能一律算成功新增函数。
- `build.json`：实际编译工具、flags 和产物 SHA256。
- `verification.json`：最终 117 项 PASS 的名字、范围和 ring 排除说明。
- `before.json`、`after.json`：四个受保护原文件身份及一致性。
- `manifest.json`：可审核文件哈希；`delivery.json`：zip 哈希、条目/CRC 与清单一致性。

`digests-initial-blocked.json` 保留早期阻断；`digests-original.json` 含早期 HMAC 失败，只使用其中已验证 SHA 部分。正确 HMAC 以 `hmac-original.json` 为准。`rea-session-install.json` 保存 unreadable_output 错误，不是成功证据。没有从这些失败记录推导“系统不支持该功能”。

## 仿真范围说明

平台采集 fixture 与事件 fixture 分开验证：事件实验替换设备、应用字段值；采集实验执行来源入口并替换平台 API 返回值。pipeline 串接 event、converter 和 ring 的原函数入口，密码主体/JSON 在原指令中执行；测试表中列出的 modeled boundaries 始终适用。单槽输出区存在逐字节差分证据，多槽成功、并发和真实网络没有等价结论。
