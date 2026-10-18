# Prism 旧版小样本专项 · 2026-10-18 r1

PSR_20250811.531a9c4：只深入 Xposed/Epic、七条虚拟环境/Superuser 路径、maps event20、status 调试检查，并交付独立 C++17 重建。

- Xposed：已加载类查找、disableHooks、反射字段/方法回退、空回调数组写入、0/1/2/3 状态和栈前缀。
- 路径：七条固定顺序，fstatat(AT_FDCWD,...,0)，首次成功短路。
- maps：getline 尾字节、>=6 字段与 %n 边界、大块可执行匿名映射计数、基线回绕、错误诊断 `8)`。
- status：511字节块、固定 substr、stoi、State 精确匹配返回6、EOF -1、fd0异常。

验证：38组核心断言、12个JNI场景、83对原始字符串getter/converter均通过，ARM64/API24共享库编译链接完成。未在Android上执行。ART枚举输入、baseline16后续写入者、原终止后端和异常畸形输入边界在报告中明确保留。

完整包共 234 项，16.85 MiB，含源码、报告、精简本轮证据、所选原始/解包样本、一个最新标注IDA数据库和前轮旧件历史证据。工具下载、SDK缓存、临时数据库、重复IDB和现代r1归档未重复打包。

SHA-256：`469e5a6e1fcb6b0338980e763c2bafe6ed1f92b8191a797e8f5aac365cb08b1e`。附独立校验文件、逐文件清单和验证记录。既有现代研究r1及PrismDetector v1.2.0版本关系保持原有含义。
