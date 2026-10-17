# 历史清单复核

这张表比较历史记录与本次读取到的文件；归档拷贝校验使用另一份新清单，二者不混为一项验收。

| 历史 manifest | 匹配 | 不匹配 | 当前快照中缺失 |
| --- | ---: | ---: | ---: |
| `research/chain_closure_20261018/manifest.json` | 191 | 0 | 0 |
| `research/mcp_clock/manifest.json` | 178 | 1 | 0 |
| `research/environment_memory/manifest.json` | 77 | 0 | 0 |
| `research/device_identity/evidence/manifest.json` | 517 | 0 | 0 |

四链 191 项含 185 项产物和 6 项复用源码依赖。历史 environment 数据库保护异常仍以四链 verification 为准，不因四链 manifest 对其交付快照匹配而消失。

## `research/mcp_clock/prism-mcp-clock.i64`

- 历史值：`3b50b736e8b22c6203e5c86975b0d9a1f44bf26483afb71d1a90a723692cd51d`
- 当前值：`d6de17313b40b3d55a15af2e54e1d3bd3d0984b7b8c57835c7f9fa40f1f734a0`
- 状态：`mismatch`。

本次只读取并保存当前文件；归档前后源文件哈希一致。现有比较不能证明历史变化的原因或只是数据库元数据变化。旧 manifest 和当前数据库均保留。

完整逐文件结果：[historical-manifest-audit.json](historical-manifest-audit.json)。
