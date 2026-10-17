# PrismSUN-Reverse

EaseCation 棱镜反作弊部分检测点的逆向产物、报告和基于已有证据重建的 C++ 代码。**这不是 PrismSUN 原始源码，也没有声称覆盖所有检查点。**

当前研究快照：**2026-10-18 r1**。最新四链包括 TracerPid、seccomp/SIGSYS、maps 与四库组合、event22；其他专项包括无障碍、输入法、设备身份、MCP 文件与 RNG 时钟支持。

## 关联应用

[PrismDetector](https://github.com/BestPVPNa1Xue/PrismDetector) 是使用部分研究成果构建的独立 Android 检测应用，采用 C++ 检测引擎与 Ruru UI。本次归档对应 [PrismDetector v1.2.0](https://github.com/BestPVPNa1Xue/PrismDetector/tree/v1.2.0)，源码提交 `c7c2c4ab600e32df694cb386cbe56925b370334e`。

本仓库负责研究源码、报告和证据；应用仓库负责 APK、UI 与平台集成。KeyMapper 特征、Minecraft 包体积/证书基准和北京时间校对中的应用规则应与原 Prism 已证逻辑分别理解。具体对应关系见 [RELATED_PROJECTS.json](RELATED_PROJECTS.json)。

## 获取完整成果

- [完整研究归档 Release](https://github.com/BestPVPNa1Xue/PrismSUN-Reverse/releases/tag/research-2026-10-18-r1)
- [下载完整 ZIP，248.94 MiB](https://github.com/BestPVPNa1Xue/PrismSUN-Reverse/releases/download/research-2026-10-18-r1/PrismSUN-research-20261018-r1.zip)
- [归档 SHA-256](https://github.com/BestPVPNa1Xue/PrismSUN-Reverse/releases/download/research-2026-10-18-r1/PrismSUN-research-20261018-r1.zip.sha256)
- [归档验证记录](https://github.com/BestPVPNa1Xue/PrismSUN-Reverse/releases/download/research-2026-10-18-r1/PrismSUN-research-20261018-r1.verification.json)

完整 ZIP 保留 1,886 个文件条目，SHA-256 为 `27282f01ed372001fb5ddac7a2505785909d8b65cb4f0574d23dcb047c1a6fde`。这是已验证归档的原样发布；它包含 IDA 数据库、原样本、已编译产物、应用快照和历史证据。

Git 主分支提供便于浏览的源码、报告及文本证据。大文件随 Release 提供；报告中指向这些文件的链接转到完整归档下载。原始证据不改写，阅读副本与归档之间的关系记录在 `REPOSITORY-MANIFEST.json`。

## 目录与阅读顺序

| 目录 | 内容 |
| --- | --- |
| [00_guide](00_guide/) | 当前状态、架构、模块对照、历史清单复核及完整归档索引 |
| [01_source/research](01_source/research/) | 重建 C++、测试、构建及分析脚本，保留模块相对依赖 |
| [02_reports/research](02_reports/research/) | 报告阅读副本，文件链接适配 Git/Release |
| [03_evidence](03_evidence/) | 原始指令/反编译导出、历史验证、字节不变的原始报告 |
| `04_binaries` 至 `08_history` | 完整内容在 Release，仓库目录提供导航说明 |
| [09_tools](09_tools/) | 归档打包、校验、布局恢复和仓库内容校验工具 |
| [releases](releases/) | 冻结归档的清单、校验及发布说明 |

建议从 [当前状态](00_guide/CURRENT_STATUS.zh-CN.md)、[架构](00_guide/ARCHITECTURE.zh-CN.md) 和 [模块对照](00_guide/MODULE_MAP.zh-CN.md) 开始，再读 [最新四链报告](02_reports/research/chain_closure_20261018/REPORT.zh-CN.md)。

## 构建与校验

源码模块内部相对路径保持；为恢复历史脚本依赖的 `evidence`、`build` 与文档布局，推荐下载完整 ZIP 后按 [恢复说明](00_guide/BUILD_AND_RESTORE.zh-CN.md) 操作。该说明中的 `verify_bundle.py` 和 `restore_workspace.py` 用于完整归档，不用于本 Git 浏览视图。

Git 浏览视图的文件校验：

```powershell
python ./09_tools/verify_repository.py
```

四链历史记录为 112 项宿主核心检查、10 项 JNI mock，通过 ARM64/API24 交叉编译；不等同于 Android 原件等价验证。旧聚合 SO 未纳入最新四链，最新四链单独产物和依赖在归档中。

## 已知边界与来源

event20 的部分状态来源和解析边界、宿主门控、完整调度/传输及服务端语义仍有缺口。真实类名单和进程现场属于外部输入。历史环境数据库与 MCP/时钟数据库的哈希异常保留在 [清单复核](00_guide/HISTORICAL_MANIFEST_AUDIT.zh-CN.md)，没有被新归档校验覆盖掉。

原始报告可能带有历史工作区路径和阶段性结论，按最新专项及记录时间理解。历史 REA 文件仅作为既有来源保存，本轮整理和发布未调用 REA。样本、数据库、第三方参考材料与重建代码的来源分别保留；应用中的 Ruru Apache-2.0 归属见应用仓库 NOTICE 和 LICENSE-Ruru。
