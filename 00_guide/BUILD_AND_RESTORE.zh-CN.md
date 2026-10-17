> 本页命令用于完整 Release 归档解压目录；Git 浏览视图请运行 `09_tools/verify_repository.py` 校验。

# 校验、恢复与构建入口

需要 Python 3.11 或更新版本。解压后先运行只读校验：

```powershell
python .\09_tools\verify_bundle.py .
```

也可以直接校验 ZIP：`python verify_bundle.py PrismSUN-research-20261018.zip`。校验逐个读取所有文件，检查清单、大小、SHA-256，并由 ZIP reader 检查 CRC；不会加载或运行归档中的 SO/EXE/IDA 数据库。

分类后的代码位于 `01_source/research`，源码内部的模块相对路径保持。为使历史脚本的 `evidence`/`build` 输出与报告布局都恢复一致，推荐复制到一个新的工作目录：

```powershell
python .\09_tools\restore_workspace.py --output D:\PrismSUN-restored --scope research-source
```

`research-source` 只恢复源码、测试和构建/分析脚本；`research` 还原全部研究文档、原始证据、已存产物、原样本和 IDA 数据库；`all` 额外还原应用及历史发布包。`--dry-run` 校验将要恢复的输入而不复制。目标必须不存在，不覆盖原工作区。阅读副本不参加恢复，恢复的是逐字节原始文档。

最新四链的历史构建入口（由使用者在恢复后按需执行，本次打包未重跑）：

```powershell
Set-Location D:\PrismSUN-restored
& .\research\chain_closure_20261018\scripts\build.ps1 -HostCompiler 'C:\path\to\g++.exe' -Ndk 'C:\path\to\android-ndk'
```

该脚本运行宿主测试并交叉编译 Android ARM64/API24，不执行原 SO。其余模块入口在各自 `scripts/build.ps1` 和 README。历史分析脚本可能写死原工作区、工具链路径或依赖 Unicorn/IDA；保留它们用于追溯，不把全部脚本声明为解压即运行。分析脚本与重建源码构建不是同一流程。

旧聚合构建入口 `research/scripts/build_all_detections.ps1` 尚未合入四链，不用它代表最新模块。应用源码在 `07_application/PrismDetector/source`，构建遵循其中 README；签名私钥和 SDK/NDK 工具链不在包内。

原始文档和历史 JSON 中的绝对路径属于取证内容，未改写。阅读副本只改 Markdown 文件链接；不能解析的旧链接转到 FILE_INDEX.csv，并在 report-link-audit.json 中保留原目标。
