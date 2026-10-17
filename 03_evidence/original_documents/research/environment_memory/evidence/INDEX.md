# 环境内存专项证据索引

## 本次直接IDA证据

| 文件 | 用途/限制 |
| --- | --- |
| [ida-0x449dd0.json](ida-0x449dd0.json) | 文件基线、最多两段、掩码与初始化标志 |
| [ida-path-test-asm.json](ida-path-test-asm.json)、[ida-0x26b1f0.json](ida-0x26b1f0.json) | 基线路径首字节比较；恢复后的0x44b0f4伪代码仍有JUMPOUT，以汇编为准 |
| [ida-0x44d0b8.json](ida-0x44d0b8.json)、[ida-maps-asm.json](ida-maps-asm.json) | 路径一致性、整批基址选择、首个可执行映射提前返回 |
| [ida-0x18b190.json](ida-0x18b190.json)、[ida-0xcb11c.json](ida-0xcb11c.json) | 字符串相等/空判断，支持路径检查解释 |
| [ida-0x44a5c0-recovered.json](ida-0x44a5c0-recovered.json) | vector empty；57表示候选向量为空 |
| [ida-0x44c594.json](ida-0x44c594.json) | 掩码产生入口；随机性未定 |
| [ida-0x5cc630.json](ida-0x5cc630.json) | maps读取/格式/权限；过滤器未完整化简 |
| [ida-0x5f917c-recovered.json](ida-0x5f917c-recovered.json)、[ida-0x5fb6b0-recovered.json](ida-0x5fb6b0-recovered.json) | 过滤器成功反编译但仍有严重栈别名，不能视作已验证源码 |
| [ida-0x34adcc.json](ida-0x34adcc.json)、[ida-0x6f4218.json](ida-0x6f4218.json) | 输入法枚举和首次/变化消费者 |
| [ida-0x66e838.json](ida-0x66e838.json)、[ida-0x68cbe0.json](ida-0x68cbe0.json) | event21/24状态到载荷 |
| [ida-0x6ab3d8.json](ida-0x6ab3d8.json)、[ida-0x6ae288.json](ida-0x6ae288.json)、[ida-0x6b0998.json](ida-0x6b0998.json) | 类查询与配置容器访问；没有实际名单 |
| [ida-0x47df58.json](ida-0x47df58.json)、[ida-0x471c8c.json](ida-0x471c8c.json) | seccomp聚合与仍不完整的原因码生产者 |
| [ida-bounded-string-search.json](ida-bounded-string-search.json) | IDA识别字符串范围内的零命中，不覆盖加密/动态配置 |

`ida-0x40fd54.json` 只得到JUMPOUT，不能代替历史三页环境汇编。首次 `ida-0x44a5c0.json`、`ida-0x5f917c.json` 等文件保存了失败记录；带 `-recovered` 的文件才是恢复边界后的结果。成功反编译也不意味着语义已经完全证明。

## 历史证据复用

- [inherited-string-evidence.json](inherited-string-evidence.json)：摘录29项与输入法/环境/状态读取有关的调用端字符串解码，来源 `research/evidence/stage2_strings.json`。
- [digest-differential.json](digest-differential.json)：此前6个摘要原指令fixture，返回值、update字节与oracle相符。
- [ime-hash-differential.json](ime-hash-differential.json)：此前9个输入法哈希原指令fixture，包括排序输出与update字节。
- [环境第一页](../../evidence/environment_asm_0.json)、[第二页](../../evidence/environment_asm_256.json)、[第三页](../../evidence/environment_asm_512.json)：完整性调度和状态写入。IDA的指令项清单有跳过定义为数据字节的问题，不当成原ELF每条指令均列出。
- [旧seccomp聚合](../../evidence/differential_policy.json)、[旧类查询](../../evidence/differential_class_probe.json)：分别704/404个有界fixture；本轮未重跑。

历史 `rea-evidence-2026-10-16.json` 保留原样。本次续接没有使用REA插件。

## 新代码验证

[host-tests.json](host-tests.json)、[jni-tests.json](jni-tests.json)、[build.json](build.json)、[offline-baseline.json](offline-baseline.json)、[verification.json](verification.json) 和 [manifest](../manifest.json)。

宿主模型73项含15项保存结果比对，JNI mock8场景单独计数。没有把它们相加后标记为原件全链路等价测试。
