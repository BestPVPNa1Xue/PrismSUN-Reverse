# 无障碍名称数组哈希：0x6d4374

范围仅限 `0x6cf0c8` 无障碍结果消费者直接调用的名称数组哈希。样本为 `D:/PrismSUN/libprism-sun.so`，SHA-256 `92e7d4adda7e222aa9dce389009a186adabb2602b80d618d417e0f6d509adaf4`。

## 已证实的完整算法

1. 参数是 `std::vector<std::string>`，元素为 24 字节 libc++ 字符串。哈希函数自身对传入数组就地排序；`0x6cf0c8` 在 `0x6cf440` 先用 `0x191ad8` 复制列表，所以调用者原列表/JSON载荷顺序不因本函数排序而变。
2. 排序为无符号字节词典序，短前缀在前，区分大小写，不去重、不裁剪、不作 Unicode 归一化。
3. `0x6d680c`、`0x6d7108` 解码算法名称 `CRC32`；`0x109f10` 是 Botan 哈希工厂调用，不是盐或前缀输入。
4. 按排序后的顺序，对每条名称先输入 `data(), size()` 全部原始字节，然后再输入一个 `0x00`。没有列表长度、元素数量、长度字段、逗号、冒号或 JSON 引号参与哈希。
5. CRC 使用 CRC-32/IEEE（反射多项式 `0xedb88320`），初始状态 `0xffffffff`，逐字节 `state = table[(state ^ byte) & 0xff] ^ (state >> 8)`，最终异或 `0xffffffff`。
6. Botan 输出完整 **4 字节大端 CRC 值**；`0x6d4848..0x6d4860` 用 `__memcpy_chk(...,4,4)` 拷贝到 `uint32_t`，在 ARM64 小端主机读回。因此本函数返回 `bswap32(standard_crc32(message))`。这里没有从更长密码摘要截取 32 位：原算法输出本来就是 4 字节。

等价表达式：

```text
ordered = unsigned_byte_lexicographic_sort(copy(names))
message = concat(name_bytes + 00 for name_bytes in ordered)
result = little_endian_uint32(big_endian_bytes(CRC32_IEEE(message)))
```

## 地址证据

| 地址 | 作用 | 证据 |
|---|---|---|
| `0x6d4374..0x6d49a8` | `.eh_frame` FDE 确认的完整函数 | `hash-6d4374.asm`；有界原件指令差分 |
| `0x6d447c..0x6d4498` | 获取 begin/end 并排序 | `0x189c08 → 0x22f618 → 0x22f6d0 → 0x22f96c → 0x22fb48` |
| `0x6d4530..0x6d456c` | 名称 `data/size` 更新 | `0x19c47c`、`0xd038c`、`0x10a218` |
| `0x6d4574..0x6d4588` | 每条名称后的 1 字节 NUL 更新 | 所有动态 `update_chunks_hex` |
| `0x791228` | 原件仿真中实际构造的 Botan CRC32 vtable | `hash-virtual-table.json` |
| `0x195f58` | `output_length() == 4` | `hash-0x195f58-decompile.json` |
| `0x1053a8` | CRC32 update 虚函数，内部状态在 `this+8` | `hash-0x1053a8-decompile.json` |
| `0x7a88a0` | 原件运行时解码后的 256×4 CRC 表 | `hash-crc-table.json`，全部条目匹配 IEEE 多项式 |
| `0x106128` | final：取反、输出、重置状态为 `-1` | `hash-0x106128-decompile.json` |
| `0x1d615c` | 输出 4 字节的下层包装 | `hash-0x1d615c-decompile.json` |
| `0x6d4848..0x6d4860` | 复制摘要并按本机小端读取 `w21` | 原始 ELF 汇编及差分 |

`hash-0x6d4374-decompile.json` 曾出现 IDA 的 `JUMPOUT` 不完整结果，**不作为完整控制流证据**。函数边界、汇编和直接执行来自原 ELF；不存在以不完整伪代码补猜算法的情况。

## 边界与比较语义

| 名称数组（测试字节） | 原件返回值 |
|---|---:|
| `[]` | `0x00000000` |
| `[""]` | `0x8def02d2` |
| `["", ""]` | `0xff12d941` |
| `["a"]` | `0x19483f3d` |
| `["a", "b"]` | `0x5f4615f5` |
| `["b", "a"]` | `0x5f4615f5` |
| `["a", "a", "b"]` | `0x1fe43ba6` |
| `["a\\0b"]`（原始嵌入 NUL） | `0x5f4615f5` |

输入顺序改变不改变哈希；重复名称会额外输入一次名称和终止字节。空列表与单个空字符串不相同。计数并未显式编码，但 NUL 终止字节使空项与重复项影响 CRC。

这是 32 位状态指纹，不能用相等值证明数组严格相等。CRC 碰撞自然存在；另外，允许任意原始 NUL 的抽象 `std::string` 输入下，`["a", "b"]` 和 `["a\\0b"]` 本来就编码成相同字节。这个构造仅说明序列化边界，不表明 Android 实际服务名会包含原始 NUL。JNI 获取字符编码方式应以采集链证据为准；本函数本身不进行编码转换。

消费者在 `0x6cf520` 只比较这 32 位指纹来判断本次是否与缓存一致。列表内容碰巧同指纹时，该比较无法发现差异。具体首轮/变化事件值由主报告和状态机源码说明。

## 可复现验证

```powershell
& 'D:/Python 314/python.exe' 'D:/PrismSUN/research/accessibility/tests/test_hash.py'
& 'D:/Python 314/python.exe' 'D:/PrismSUN/research/accessibility/scripts/hash_crc_table.py'
& 'D:/Python 314/python.exe' 'D:/PrismSUN/research/accessibility/scripts/hash_original.py' 'z' 'a'
& 'D:/Python 314/python.exe' 'D:/PrismSUN/research/accessibility/tests/test_hash.py' --retry-failed --model-dll 'D:/PrismSUN/research/accessibility/build/host/accessibility_core.dll' --dll-directory 'D:/msys64/ucrt64/bin'
```

结果：**42/42 PASS**。测试包括空列表、空名称、重复、换序、大小写和前缀、0x80..0xff 字节、UTF-8/Modified UTF-8 测试字节、原始 NUL、22/23 字节 libc++ ABI 边界、16 字节 CRC 批处理边界、长名称、24 和 129 元素排序以及 24 组固定种子随机字节数组。第 3 条命令返回 `0x06de0e77`，对应标准 CRC `0x770ede06`，精确验证字节交换。

已额外使用上面第 4 条命令，将主任务编译出的 `accessibility_core.dll` 导出 `a11y_snapshot_hash` 与全部 42 组原件向量逐项比较：**C++ 42/42 PASS**。`hash-cpp-differential.json` 保存编译产物 SHA-256 和每项结果。`--retry-failed` 复用同源 SHA-256 的已完成原件指令证据，避免重复运行所有仿真；Windows 动态链接器通过显式 `--dll-directory` 找到本机构建所用 UCRT64 运行库。

`hash-differential.json` 保存每项输入、排序后数组、每次 update 的字节、拼接消息、原件返回、参考值、步数、停止原因和模拟边界。`hash-crc-table.json` 保存解码后的全部 256 个表项和 CRC 状态。参考计算使用独立 `zlib.crc32`，不是重写原件指令后自测。

原件仿真完整执行排序、算法字符串解码、Botan CRC 工厂、CRC update/final、结果提取及清理。只模拟宿主依赖的 libc 内存原语、编译器 TLS 分配和 TLS 析构注册；任何未建模 import、目标外执行和系统调用仍停止。ELF `R_AARCH64_RELATIVE` 与调用所需 ABS64/GLOB_DAT 按装载语义在模拟内存解析，磁盘 ELF 未修改。

首次运行 41/42 通过，129 项排序触及 10 秒时间预算，结果保留为 `hash-differential-initial.json`。单用例预算增为 45 秒（指令上限仍 2,000,000）后用 `--retry-failed` 仅重跑失败项：1,162,949 条原件指令完成并通过，最终 42/42。这是仿真预算调整，不是算法修补。

## BEFORE / AFTER / ROLLBACK

- BEFORE：哈希仅被识别为 `0x6d4374`，算法/排序/终止符/端序尚未确认。
- AFTER：上述细节均有静态地址和原指令差分；共享模型源码由主任务统一实现和编译。
- ROLLBACK：本子任务没有修改样本、原数据库、设备、系统配置或反作弊运行进程；删除新增 `hash-*` 证据、`hash_*.py` 脚本、此笔记和 `test_hash.py` 即可移除本子任务产物。原件哈希记录用于核对。
