# 当前状态与历史边界

归档日期：2026-10-18；原样本 SHA-256：`92e7d4adda7e222aa9dce389009a186adabb2602b80d618d417e0f6d509adaf4`。

最新研究顺序：基础研究 → 无障碍/设备身份 → 环境内存 → MCP/时钟 → 覆盖审计 → 四链闭合 → 调试 APK 评估 → PrismDetector 1.0/1.1/1.2。历史报告中的“还没有 APK”“尚未厘清”等字样保持原文；判断现状时应按此顺序参照。

- [四链报告](../02_reports/research/chain_closure_20261018/REPORT.zh-CN.md) 是 TracerPid、seccomp/SIGSYS、maps 过滤及 event22 的最新研究入口。112/10 是宿主模型/mock 检查，不是全库覆盖率或设备检出率。
- event20 的 `state+16` 后续来源、原始错误文字及独立 raw 数字 scanner 仍未闭合；真实类名单、handler、status/maps 属于外部输入。宿主门控、全库自检覆盖、完整网络/服务端语义仍有边界。
- 原始四链 `verification.json` 保留 `passed=false`：5 个保护文件中 4 个匹配，历史 `prism-environment-memory.i64` 哈希变化。不能证明只是元数据变化。本归档不会修改此判定，也不会把新的文件拷贝校验解释为旧异常已解决。
- 本次逐项复查历史 manifest，结果保存在 [历史清单复核](HISTORICAL_MANIFEST_AUDIT.zh-CN.md)。另发现 MCP/时钟数据库当前哈希与旧 manifest 不一致；其余三份清单的条目匹配。旧值、现值和原始文件均保留，不能推断变化原因。旧清单与本次归档校验分别记录。
- PrismDetector 1.2.0 已发布，提交 `c7c2c4ab600e32df694cb386cbe56925b370334e`。应用采用 Ruru UI，包含用户指定的 KeyMapper 特征、Minecraft 包体积/证书基准和北京时间校对。这些应用规则与原 Prism 已证明的规则分开看待；MCP 文件检测没有接入应用。
- 应用的 API34 x86_64 验收见 [1.2.0 记录](https://github.com/BestPVPNa1Xue/PrismSUN-Reverse/releases/download/research-2026-10-18-r1/PrismSUN-research-20261018-r1.zip)。ARM64 真机和 API35 未实测。这个应用验收不意味着原 Prism 全链已经完成 Android 对照。

旧 REA 证据只是已有历史来源，保留原文件与来源名称；本次整理未调用 REA 或执行逆向分析，也没有重跑原样本、原指令仿真或 Android 产物。
