# AccessibilityServiceChecker 的注册、接口与调度边界

## 已确认结论

本库把无障碍采集任务注册为 **ID 38 (`0x26`)、名称 `AccessibilityServiceChecker`**。专属任务对象的虚表是 `0x793de8`，无障碍消费者是虚表 `+0x40` 对应的 `0x6cf0c8`。首次采集状态可以通过虚表 `+0x50` 查询，它读取全局上下文 `+556` 的原子布尔值。

已找到从 ELF 静态初始化、注册表插入、工厂回调到任务构造的连接。**现有证据没有给出实际调度周期、周期单位、外部触发条件或服务器开关**。返回常数 `1` 的接口不能直接翻译为“每 1 秒执行”。本轮止于专属任务进入通用注册表的边界，没有展开其他检测任务。

## 注册与构造链

```text
ELF .init_array: 0x6b6f3c
  → 0x6b6a78
    → 0x6b7340(registration_storage=0x7d09b0, key=0x26)
      → 0x4ea8b8(): shared registry singleton at 0x7d08d8
      → build callback through 0x6b7508 → 0x6b7928 → 0x6b827c
        → callback object vtable 0x793da0
      → 0x601c58(registry, 38, callback)

callback vtable 0x793da0 +0x30: 0x6bb444
  → 0x6caf5c
  → 0x6cb328
  → 0x6cbc50
  → 0x6cc6b0
  → 0x6ccb14: allocate 8-byte checker object
  → 0x6cced8: store checker vtable 0x793de8
```

上图省略只含一条跳转的 thunk（如 `0x6dd5c8`、`0x6dd5cc`、`0x6dd5dc`）。具体 xref 和 FDE 来源保留在 `evidence/hash-upstream-factory-chain.json`、`hash-upstream-registration-chain.json`、`hash-upstream-registration-chain2.json` 和逐函数 `hash-upstream-0x*.json` 中。

静态 `.init_array` 来源为既有 `research/evidence/elf_inventory.json`，其中十进制初始化地址 `7040828` 即 `0x6b6f3c`。`0x6b6cc4` 的注册调用明确传 `w1=0x26`；`0x6b73d0` 把该值和新建回调交给 `0x601c58`。

有界原件仿真验证了以下事实：

- 从 `0x6b6f3c` 开始，专属初始化代码恰好向被观测的注册入口传递一次 key `38`。
- 注册回调实际对象虚表为 `0x793da0`，invoke 位于 `+0x30`，目标 `0x6bb444`。
- 独立执行原件工厂回调后，创建出的 checker 对象虚表为 `0x793de8`。
- 名称方法 `0x6cdbec` 执行 50,323 条原始指令后，TLS 解码结果为 `AccessibilityServiceChecker`，返回字符串长度 27。

注册测试把通用注册表 singleton getter 和 insert 作为观测边界，没有模拟或启动线程调度。回调包装、任务分配、构造和虚表写入执行原件指令，内存原语遵循 `hash_original.py` 中公开的惰性 arena 模型。

## 虚接口清单

| 虚表偏移 | 实现地址 | 已证实行为 | 语义限制 |
|---:|---|---|---|
| `+0x00` | `0x6300d8` | 析构接口位置 | 未进一步展开基类清理 |
| `+0x08` | `0x6cd77c` | 调用析构并释放对象 | deleting destructor 模式 |
| `+0x10` | `0x6cdbec` | 返回名称 `AccessibilityServiceChecker` | 原件解码已验证 |
| `+0x18` | `0x6cdfb4` | 返回 `38` | 与注册 ID 一致 |
| `+0x20` | `0x6ce3ec` | 返回 `1` | 调度端如何解释尚未确认 |
| `+0x28` | `0x631408` | 返回 `0` | 调度端如何解释尚未确认 |
| `+0x30` | `0x6ce880` | 返回 `1` | 调度端如何解释尚未确认 |
| `+0x38` | `0x6ced50` | 正常路径无采集/报告业务操作 | 不能仅据此给出接口原名 |
| `+0x40` | `0x6cf0c8` | 无障碍列表采集、哈希、状态更新与结果构造 | 主报告详述 |
| `+0x48` | `0x6cf6d4` | 转调自身虚表 `+0x40` | 原件验证 `X0`、`X1`、`X8` 都传给消费者 |
| `+0x50` | `0x6cfa68` | 获取全局上下文后读取 `context+556`，返回低位布尔值 | 与消费者的“已有首次成功结果”字段一致 |

`0x6cfa68` 正常指令在 `0x6cfcb8` 获取上下文，`0x6cfcbc` 加 `0x22c=556`，`0x6cfcc0` 传 `5` 给原子读取包装 `0x4181a0`。这里的 `5` 是原子操作的 `memory_order` 参数，**不是第 5 个数组元素**。在上下文布尔字段分别为 0/1 的惰性夹具中，整个原件方法分别返回 0/1。

## 结果交付能证明到哪一步

`0x6cf6d4` 在 `0x6cf8b0..0x6cf8b8` 从对象虚表取 `+0x40` 并间接调用消费者。原件夹具验证消费者收到相同 `X0=this`、`X1=调用方参数` 和 `X8=调用方提供的结果缓冲区`；包装函数没有转换结果或单独发起网络请求。

结果消费者内部的构造、首次/变化分类及 JSON 所有权由主报告和核心差分验证覆盖。本调度分支只能说明“结果回到调用方提供的存储位置”，不能把它直接称为某条已观察到的网络上报。后续通用调用方的排队、发送、周期和调度线程属于仍需进一步追踪的边界。

## 下一精确入口与停止边界

1. `0x601c58` 是本 checker 注册进入通用 registry 的明确入口。其正常路径在 `0x601fb0` 调 `0x602d18` 查找 key，在 `0x602070`/`0x602078` 经 `0x639af4`/`0x639af8` 获取或赋值回调槽。Hex-Rays 对该函数报 `bad sp value at call`，不能直接把整份伪代码按源码使用；地址、参数和调用点可由原始汇编复核。
2. 通用 registry 对象地址 `0x7d08d8`、getter `0x4ea8b8` 是继续寻找“按 ID 38 获取任务”的入口。下一步应只针对该 key 的取出路径观察调度调用方，不扫描或反编译其它 checker 的逻辑。
3. 实际 dispatch 需要追共享调度器对 checker 虚表 `+0x40`/`+0x48` 的间接调用，并在调用点证实 `+0x20`/`+0x28`/`+0x30` 常量的含义。尚没有可引用的实际 timer callsite；因此本报告不填周期数值。

## 复现与验证

```powershell
& 'D:/Python 314/python.exe' 'D:/PrismSUN/research/accessibility/scripts/hash_scheduling.py'
```

结果：`PASS`。保留证据 `evidence/hash-upstream-scheduling-emulation.json`，包括注册参数、工厂返回、常数接口、0/1 状态查询和派发参数。名称独立解码证据为 `hash-upstream-name-emulation.json`。

BEFORE：仅知道消费者地址；注册入口、任务名、task ID、虚接口关联未建立。

AFTER：专属注册/工厂/结果交付接口已形成闭环；实际调度周期和通用发送层明确标记未解决。本分支只在新建研究副本内按 ELF FDE 定义指令和函数，没有改原 ELF、原数据库或目标运行环境。

ROLLBACK：分析定义位于可丢弃的 `research/accessibility/prism-accessibility.i64` 副本，主任务保留源数据库；新增脚本和 `hash-upstream-*` 证据可单独移除。此分支没有全局配置或设备部署需要恢复。
