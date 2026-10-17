# 模块、源码、报告与证据对照

| 模块 | 代码 | 报告 | 证据 | 状态与边界 |
| --- | --- | --- | --- | --- |
| 四链最新重建 | [src](../01_source/research/chain_closure_20261018/src/) | [报告](../02_reports/research/chain_closure_20261018/REPORT.zh-CN.md) | [evidence](../03_evidence/research/chain_closure_20261018/evidence/) | TracerPid、seccomp/SIGSYS、maps/四库组合、event22；112 项宿主核心 + 10 项 JNI mock；ARM64/API24 交叉编译；event20 仍部分重建；原库 ABI、真实输入与 Android 等价未证 |
| 环境与内存 | [src](../01_source/research/environment_memory/src/) | [报告](../02_reports/research/environment_memory/REPORT.zh-CN.md) | [evidence](../03_evidence/research/environment_memory/evidence/) | 四库 ELF/CRC 比较器、环境循环、输入法 JNI；专项原始测试/差分及构建记录；maps/Tracer/SIGSYS 的新入口以四链模块为准 |
| 无障碍 | [src](../01_source/research/accessibility/src/) | [报告](../02_reports/research/accessibility/REPORT.zh-CN.md) | [evidence](../03_evidence/research/accessibility/evidence/) | 枚举、排序/hash、变化状态机、JNI 生命周期；专属原指令/重建对照与 mock 记录；原链没有据此证明 KeyMapper 专用作弊规则 |
| 设备身份 | [src](../01_source/research/device_identity/src/) | [报告](../02_reports/research/device_identity/REPORT.zh-CN.md) | [evidence](../03_evidence/research/device_identity/evidence/) | 设备/应用字段、摘要、密码与 Android 适配；专项 manifest、verification 与差分证据；证书摘要对象与官方签名信任不是同一件事 |
| MCP 与时钟 | [src](../01_source/research/mcp_clock/src/) | [报告](../02_reports/research/mcp_clock/REPORT.zh-CN.md) | [evidence](../03_evidence/research/mcp_clock/evidence/) | MCP 文件链、时钟输入、RNG/HMAC_DRBG；46 项宿主检查；独立 HMAC 对照 98/98（历史记录）；原时钟链为 RNG 支持；北京时间校对属于应用新增功能 |
| 基础模型 | [src](../01_source/research/src/) | [历史总报告](../02_reports/research/REPORT.zh-CN.md) | [原始证据](../03_evidence/research/evidence/) | 入口指令分类、观察策略、类探测、共享 ring；四链不等于全库覆盖 |

任务 ID 与事件 ID 不可混用；接口和真实输入的边界以最新专项报告为准。
