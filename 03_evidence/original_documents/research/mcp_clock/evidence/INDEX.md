# 证据索引

所有新反编译、反汇编、虚表、RTTI 查询来自 IDA Pro MCP，会话 `6e90ea58`。JSON 优先保存 structuredContent；历史 prior 中部分文件同时保存 text/structuredContent，读取时不要重复计算。

| 结论 | 主要证据 |
| --- | --- |
| 两遍扫描主逻辑 | prior/ida-0x30b278.json、prior/decomp-0x30bb2c.json、asm-0x30b278.json、asm-0x30bb2c.json |
| /proc/ + PID + /fd | asm-0x5fedc0.json、dec-0x5fea58.json、dec-0x5feca8.json、asm-0x319fa4.json、more-1.json、asm-0x31038c.json、asm-0x30c1f0.json、decoded-constants.json |
| 严格 suffix/prefix | dec-0x30e5b0.json、dec-0x237c04.json、dec-0x2379ec.json、dec-0x237b0c.json、dec-0x1d579c.json、follow-4.json、follow-5.json |
| marker pos - 1 | asm-0x30bb2c.json 中 0x30bf80；d-0x745934.json |
| MCPK 头、XOR 07、offset24、上限64 | prior/ida-0x30e700.json（常量折叠错误须核对 asm）、asm-0x30e700.json、focus-4.json、decoded-constants.json |
| read/lseek 不检查、系统调用包装 | dec-0x311058.json、dec-0x3111d0.json、asm-0x30e700.json |
| basename + ':' + text | asm-0x30b278.json 0x30b7f4..0x30b88c、more-4.json、more-5.json、focus-4.json |
| vector 保序追加 | dec-0x30ecf4.json、verify-2.json |
| event 32 | dec-0x632054.json、prior-fresh/dec-0x632054.json |
| 四 clock ID 与 MONOTONIC 回退 | prior/clock_ids.json、dec-0x140c9c.json、dec-0x744750.json、dec-0x140f44.json、dec-0x21f710.json |
| aux32 参数、时间/PID 小端 | asm-0xf5198.json、dec-0x147280.json、dec-0x1473b8.json、asm-0x1d6994.json、asm-0x1a3d60.json |
| System RNG 实际调用 arc4random_buf | verify-3.json、rtti.json、dec-0x14716c.json、dec-0x19b244.json |
| AutoSeeded_RNG 与 HMAC_DRBG 身份 | rtti.json、verify-3.json、verify-4.json、more-6.json、dec-0x13430c.json、b-0x78fa40.json |
| SHA512 优先/SHA256 备用 | follow-2.json、b-0x7a0868.json、b-0x7a0728.json、decoded-constants.json |
| caller supplied input 分派 | focus-3.json、prior/ida-0xf5198.json |
| counter/PID/重播种/0输出 | dec-0x185168.json、dec-0x184994.json、dec-0x184df0.json、dec-0x185788.json、dec-0x147678.json |
| 初始化/丢弃1字节 | dec-0xf4388.json、dec-0xf48b8.json、dec-0xf49c4.json、dec-0x134920.json |
| 1024 间隔，65536 最大块 | rng-caller-1.json、rng-caller-2.json、rng-caller-3.json、follow-1.json、dec-0x1987b4.json |
| HMAC_DRBG update/generate | dec-0x1357ec.json、dec-0x1352b0.json |

`dec-0x30c1f0.json` 保留新副本的反编译失败，不当作成功证据；对应完整汇编可用，上轮成功输出位于 prior-fresh/dec-0x30c1f0.json。其他 failure JSON 同样保留诊断意义。报告没有以反编译是否成功代替汇编可达性判断。

验证：build.json、unit-tests.txt、oracle-tests.json、verification.json。独立 Python 对照没有执行原 ELF。源码和产物哈希在 ../manifest.json。
