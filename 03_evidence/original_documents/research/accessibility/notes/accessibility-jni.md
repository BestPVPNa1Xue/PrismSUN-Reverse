# 无障碍 JNI 生产者：已恢复的 API 链与实现契约

范围限于 `libprism-sun.so` 的无障碍 ID 枚举链。样本 SHA-256：
`92e7d4adda7e222aa9dce389009a186adabb2602b80d618d417e0f6d509adaf4`。
地址均为该 ARM64 ELF 的虚拟地址/RVA，运行时需加装载基址。

## 结论

`0x31b73c` 枚举 Android **当前已启用**的无障碍服务，以 `-1`（`FEEDBACK_ALL_MASK`）为参数，逐项获取 `AccessibilityServiceInfo.getId()`。每个 Java 字符串经 `GetStringUTFChars` 转为 modified UTF-8 后原样加入 `std::vector<std::string>`。这不是应用名称/显示标签枚举，也不是仅检查某个包名。本生产者内没有 KeyMapper 字符串比较或包名过滤；不能将用户线索写成该函数的已证实特定检测。

其输入为当前线程的 `JNIEnv*`（X0）；结果是调用者通过 AArch64 X8 提供的 vector 对象。反编译器把清理函数留下的 X0 显示为返回值，不能据此把本函数建模成返回整型检测分数。

## 实际调用链

```text
0x31b73c(env, result@X8)
  result = empty vector
  0x2db974(env):
    FindClass("android/app/ActivityThread")
    GetStaticMethodID("currentActivityThread", "()Landroid/app/ActivityThread;")
    CallStaticObjectMethodV(...)
    GetMethodID("getApplication", "()Landroid/app/Application;")
    CallObjectMethodV(...)
    DeleteLocalRef(activityThread instance/class)
    -> Application local reference
  FindClass("android/content/Context")
  GetStaticFieldID("ACCESSIBILITY_SERVICE", "Ljava/lang/String;")
  GetStaticObjectField(...)
  GetMethodID("getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;")
  CallObjectMethodV(application, ..., ACCESSIBILITY_SERVICE)
  FindClass("android/view/accessibility/AccessibilityManager")
  GetMethodID("getEnabledAccessibilityServiceList", "(I)Ljava/util/List;")
  FindClass("java/util/List")
  GetMethodID("get", "(I)Ljava/lang/Object;")
  GetMethodID("size", "()I")
  FindClass("android/accessibilityservice/AccessibilityServiceInfo")
  GetMethodID("getId", "()Ljava/lang/String;")
  list = CallObjectMethodV(manager, getEnabled..., jint(-1))
  if list != null:
    count = CallIntMethodV(list, size)  // only once
    for signed int i = 0; i < count; ++i:
      info = CallObjectMethodV(list, get, i)
      id = CallObjectMethodV(info, getId)
      value = 0x2e5024(env, id):
        if id == null: empty string
        else chars = GetStringUTFChars(id, nullptr)
        if chars == null: empty string
        else std::string(chars); ReleaseStringUTFChars(id, chars)
      result.push_back(value)
      destroy temporary string; DeleteLocalRef(id); DeleteLocalRef(info)
  DeleteLocalRef(all remaining local objects/classes)
```

`ACCESSIBILITY_SERVICE` 的值读取自 Android class；样本在这里并未直接用硬编码 `"accessibility"` 替代该字段读取。

## 函数地图及 JNI 表偏移交叉确认

以下偏移按 AArch64 的 8 字节指针表核实。`slot = offset / 8`；完整原字节、指令及 FDE 范围保存在 `evidence/jni-raw-wrappers.json`，并有便于人工查看的 `.txt`。反编译在平坦化控制流中仍会出现错误参数/不可达垃圾指令，表格以真实 load + `blr` 数据流为准。

| 函数 | JNI 操作/契约 | 表偏移 / slot | 原字节证据指令 |
|---|---|---|---|
| `0x2db974` | `ActivityThread.currentActivityThread().getApplication()` | 组合 | `jni-decompile-0x2db974.c` + 字符串 |
| `0x2dce08` | `FindClass` | `0x30` / 6 | `0x2dd06c ldr x8,[x8,#0x30]`; `0x2dd074 blr x8` |
| `0x2e00cc` | `GetStaticMethodID` | `0x388` / 113 | `0x2e031c`; `0x2e032c` |
| `0x2e0a2c` | `CallStaticObjectMethodV` | `0x398` / 115 | `0x2e0ce0`; `0x2e0d24` |
| `0x320984` | `GetStaticFieldID` | `0x480` / 144 | `0x320af4`; `0x320b04` |
| `0x320d04` | `GetStaticObjectField` | `0x488` / 145 | `0x320f80`; `0x320f8c` |
| `0x2e3e98` | `GetMethodID` | `0x108` / 33 | `0x2e4114`; `0x2e4144` |
| `0x2e4448` | `CallObjectMethodV` | `0x118` / 35 | `0x2e4680`; `0x2e46c4` |
| `0x332358` | `CallIntMethodV` | `0x190` / 50 | `0x332500`; `0x33252c` |
| `0x2e5254` | `GetStringUTFChars` | `0x548` / 169 | `0x2e54c4`; `0x2e54e8` |
| `0x2e579c` | `ReleaseStringUTFChars` | `0x550` / 170 | `0x2e59d4`; `0x2e59e0` |
| `0x301194` | `DeleteLocalRef` | `0xb8` / 23 | `0x3013a0`; `0x3013a8` |
| `0x331f98` | scoped local-ref 的非空测试 | 无 JNI 调用 | `0x33216c ldr x8,[x8,#8]`, `cmp x8,#0`, `cset w8,ne` |
| `0x2e5024` | `jstring` → native string，空值变空串 | 组合 | `jni-decompile-0x2e5024.c` |
| `0x2e1048`, `0x2dd338`, `0x2e8568` | 保存 `{env, local_ref}` | 无 JNI 调用 | 构造包装器 |
| `0x2e4dd0`, `0x2e4ef4`, `0x2e8d48` | 两字段非空时调用 `0x301194` | DeleteLocalRef | 对象、class、string 的 scoped 析构 |
| `0x13f5e4` | 将临时 string 插入输出容器 | 无 JNI 调用 | 主函数 `0x31c440` |

关键生产者 callsite（以 raw BL 地址而非伪代码行末地址为准）：

- `0x31ba7c`：获取 Application；`0x31bac4`：Context class。
- `0x31bb3c` / `0x31bb68`：静态服务字段 ID / 字段对象。
- `0x31bc0c` / `0x31bc68`：获取 / 调用 `getSystemService`。
- `0x31bd70`：取得 `getEnabledAccessibilityServiceList` method ID。
- `0x31be54` / `0x31beec`：取得 `get` / `size` method ID。
- `0x31bfbc`：取得 `getId` method ID。
- `0x31c004 mov w3,#-1`; `0x31c008 bl 0x34aaf0`，后者直接跳转 `0x2e4448`。
- `0x31c034` / `0x31c040`：list 非空测试及分支。
- `0x31c2e8`：只读取一次 size；`0x31c35c cmp w8,w9`、`0x31c360 b.lt`：有符号循环上限。
- `0x31c3a8`：List.get；`0x31c3ec`：getId；`0x31c428`：转换字符串；`0x31c440`：插入 vector。
- `0x31c44c` / `0x31c454` / `0x31c45c`：临时 string / Java id / Java info 清理。

## 补齐上一轮缺失的短字符串

旧 `decode_prefixes.py` 只保留 `len(raw)>4` 或包含可打印长串的写入块，恰好丢失两项加密的四字节 token。本轮只执行它们的本地 ARM64 writer 前缀，在第一条调用前停止；没有转发任何宿主调用。随后采用上一轮 wrapper 真实寄存器流恢复的 XOR key 解码。

| writer / data | 原始生成字节 | key | 明文含终止符 | 生产者 writer/decode callsite |
|---|---|---|---|---|
| `0x329e7c` / `0x7ac990` | `b4 7a 09 a3` | `0xfd4ff1bda37d1fd3` | `67 65 74 00` (`get`) | `0x31bdd8` / `0x31bde0` |
| `0x32ce7c` / `0x7ac9f0` | `69 0c 22 0d` | `0xad7941110d6b2541` | `28 29 49 00` (`()I`) | `0x31be98`（经 thunk）/ `0x31bea8` |

`scripts/jni-short-strings.py` 包含断言，结果在 `evidence/jni-short-strings.json`。其它 14 个主生产者 token 和 5 个 Context 获取 token 复用 `research/evidence/stage2_strings.json` 的 `verified_direct_register_flow` 证据。

## 空值、错误与顺序语义

- list 为 null 或 `size()==0` 时，输出空 vector；`size()<0` 虽违反 Java List 契约，原有 signed 循环同样不会进入。
- 顺序和重复 ID 保留；没有本地排序、去重、过滤空串、标签查询、包安装查询。
- 非空 list 的元素没有显式 null 保护，直接进入 getId 调用。class/method/field 的失败也没有正常业务失败路径。
- 在本链正常路径及直接 JNI 包装器里，未见 `ExceptionCheck`、`ExceptionOccurred` 或 `ExceptionClear`。不能将“C++ unwind 清理”误写成“Java 异常被捕获处理”。Java 调用失败后可能遗留 pending exception；Android VM 的实际后果需设备环境验证。
- `0x2e5024` 对 null jstring 或 null UTF chars 返回空 native string；原函数没有据此区分 OOM/Java 异常/合法空值。
- UTF chars 在 native string 构造成功后被 release；每轮 Java id 和 info 局部引用均删除。正常结束时删除 list、info class、List class、manager class、manager、服务名、Context class、Application。
- 输出分配/拷贝触发 C++ 异常时存在析构与 unwind 路径，主函数 `0x31c4d0` 等和 `0x31c584` 后的 landing pads 可见。原始转换函数不是 UTF chars RAII；不能声称所有 native 分配异常路径都保证释放 UTF chars。
- 获取 Context 涉及 Android hidden API；当前线程附加状态、Android 策略、Application 初始化时机是否满足，不能由静态样本证明。

## 可编译重建适配器

文件：`src/accessibility_jni.hpp`、`src/accessibility_jni.cpp`。

```cpp
auto observed = prism::accessibility::enumerate_enabled_services(env);
if (observed.complete) {
    // observed.ids is a complete enabled-service-ID snapshot.
    // Feed it into the separately reconstructed state machine.
}
```

另有 `enumerate_enabled_services_from_context(env, context)` 供宿主显式传入 Context，直接执行同一个枚举体；这是重建接口，不表示原样本有此入口。传入 Context 为借用引用，不由适配器删除。所有字符串均保持 JNI modified UTF-8；没有把它误称为严格 UTF-8。

与原样本的明确区别：

1. 每步检查 Java pending exception，停止并返回分阶段诊断；不清除异常，不产生错误的完整快照。`complete=false` 时 IDs 仅为部分观测。
2. 对必要 class/method/field/对象及 list 元素增加 null 保护。合法 null list 和 null string 保留已观察到的空输出语义。
3. UTF chars 使用 RAII，即使 C++ string 分配抛异常也能释放；C++ 异常仍传播给调用方。
4. 原 Context helper 在返回 Application 前就释放 ActivityThread 实例/class；适配器保持它们至整个调用结束，仍在同一次调用内释放，不创建 global ref。
5. 不重现混淆、函数前缀完整性保护、堆栈 canary、容器 ABI 或无意义 X0 清理返回值；这些不是无障碍枚举语义。

这是一份恢复可读逻辑的实现，不是原 SO 的 ABI 兼容替代品。

## 已执行验证

`scripts/jni-build.ps1` 执行：

- Windows host `clang++ -std=c++17 -O2 -Wall -Wextra -Werror`，以 Android 的 VM-neutral `jni.h` 构建 fake-JNIEnv 验证程序。
- 8 项场景：普通 3 条记录（含重复与顺序）、null list、空 list、null ID 和 null UTF chars、第二项 Java 异常（保留首项但 incomplete）、入口已 pending exception、null env、借用 Context 路径。
- 对所有场景验证 method signature、mask `-1`、size 只调用一次、local refs 全部回收、UTF chars 释放次数、异常未被吞掉。输出 `PASS: 8 JNI adapter scenarios; signatures, mask, ordering, cleanup, pending exception`。
- 对 NDK `JNINativeInterface` 使用 11 个 `offsetof` 编译期断言，确认上表中原始指令所用 JNI table 偏移。
- NDK r27 clang，`--target=aarch64-linux-android24 -std=c++17 -O2 -Wall -Wextra -Werror -fPIC -c`，产物 `build/accessibility_jni.o`。

构建结果及哈希在 `evidence/jni-build-verification.json`。这是源码编译和模拟 JNI 契约验证，未连接 Android 设备，未声称运行时已取到真实服务列表。

## 来源索引与剩余边界

- `research/decompiled/0x31b73c.json`：继承的主函数反编译。
- `research/evidence/stage2_strings.json`、`stage2_keys.json`：继承的字符串证据和解密参数。
- `evidence/jni-raw-wrappers.json` / `.txt`：本轮 76 个函数/跳板的原始 ELF 字节反汇编和 FDE 范围（含补充的环境生命周期）。
- `evidence/jni-decompile-0x*.json` / `.c`：对独立 `prism-accessibility` 数据库的只读 MCP 完整返回和便读代码。部分最初失败在补全 FDE 定义后重查成功；不能把平坦化中的错误类型当成真实 JNI 类型。
- `evidence/jni-short-strings.json`：新补的两个短 token。
- `evidence/jni-build-verification.json`：实现的编译、mock 验证、源码/产物哈希。

生产者接口契约已经收敛；不存在仍需猜测的 method 名称、签名、mask 或输出字段。未知项保留在实际 Android hidden API/启动时机、异常触发后的 VM 行为与真实设备结果。KeyMapper 是否被下游专门判定，超出本生产者证据，只能由消费者及外部策略另行证明。

## 补充：消费者外层的 JNI 环境获取与线程附加生命周期

`0x6cf0c8` 在调用枚举生产者前通过 `0x306df0` 建立一个 scoped JNI 环境对象，枚举结束后在 `0x6cf354` 调用 `0x3078cc` 销毁该对象。**外层会按需附加 native 线程；仅借用 JNIEnv 的生产者自身不附加。** 因此不能把上文的 adapter 输入契约推论为原完整链完全不执行 AttachCurrentThread。

恢复出的调用和对象布局如下：

```text
0x306df0(out@X8)
  0x308130 → 0x2b2630: 取得全局持有的 singleton 对象
  0x3071a8(singleton): 解引用对象首 qword，得到 JavaVM*
  0x305790(out@X0, vm@X1): 构造 Scope

Scope:
  +0x00 JavaVM* vm
  +0x08 JNIEnv* env
  +0x10 uint8_t attached_by_this_scope   // 只使用 bit 0
```

`0x2b2630` 使用全局 holder `0x7d06b8` 和 guard `0x7d06c0`；此边界只需确认返回 singleton 的首字段被当作 JavaVM 使用，不扩展分析其它 singleton 成员或初始化用途。`0x3071a8` 的正常路径在 `0x30728c` 读取其首 qword。旧 Hex-Rays 在 `0x305790` 的平坦化中把 X0/X1 与保存寄存器混淆成“`*a2=a2`”，不能照抄；真实指令 `0x305cc4/0x305cc8` 保存 scope/VM，`0x305cdc` 将 VM 写入 scope 首字段，原指令合成执行也验证了实际布局。

等价逻辑：

```cpp
scope.vm = vm;
scope.env = nullptr;
scope.attached = false;
if (vm != nullptr) {
    int rc = vm->GetEnv(reinterpret_cast<void**>(&scope.env), JNI_VERSION_1_6);
    if (rc == JNI_OK) {
        scope.attached = false;  // 借用已附加线程
    } else if (rc == JNI_EDETACHED) {
        rc = vm->AttachCurrentThread(&scope.env, nullptr);
        if (rc == JNI_OK) scope.attached = true;
        else { scope.env = nullptr; scope.attached = false; }
    } else {
        scope.env = nullptr;
        scope.attached = false;
    }
}
// 0x3078cc 析构
if ((scope.attached & 1) && scope.vm != nullptr)
    scope.vm->DetachCurrentThread(); // 不检查返回值
```

这里使用 `AttachCurrentThread`，不是 daemon 版本；没有线程名称参数，传入的 `JavaVMAttachArgs*` 为 null。只有 `GetEnv` 返回 `-2` 才尝试附加；`JNI_EVERSION=-3` 或其它错误不附加。已有 JNIEnv 不被该 scope detach。null JavaVM 保护在原函数中已经存在，并非新增增强。

| 边界 | 原始证据 | 确认操作 |
|---|---|---|
| `0x308130` | 单指令 `b 0x2b2630` | singleton getter 跳板 |
| `0x3071a8` | 正常路径读取输入对象首 qword | 取 JavaVM* |
| `0x305790` | `0x305ce4` env=0；`0x305cec` flag=0 | Scope 初始化 |
| `0x306404` | `0x30667c ldr x8,[x8,#0x30]`; `0x306688 blr x8` | **JavaVM** table slot 6: GetEnv |
| `0x305dac/0x305db0` | `mov w2,#6`; `movk w2,#1,lsl#16` | JNI 版本 `0x00010006`（1.6） |
| `0x305db4` | `bl 0x306404`; X1=&scope.env | GetEnv 调用 |
| `0x305e78` | `cmn w8,#2` | 比较 JNI_EDETACHED=-2 |
| `0x306930` | `0x306b64 ldr x11,[x11,#0x20]`; `0x306b88 blr x11` | JavaVM table slot 4: AttachCurrentThread |
| `0x305ed8/0x305edc` | X2=0；`bl 0x306930` | Attach args=null |
| `0x305f7c` | `strb w9,[x8,#0x10]`, W9=1 | 本 scope 新附加成功标志 |
| `0x3078e8..0x307910` | 检查 +16 bit0 和 vm!=0，再调用 `0x3073fc` | 条件析构 detach |
| `0x3073fc` | `0x307654 ldr x8,[x8,#0x28]`; `0x307658 blr x8` | JavaVM table slot 5: DetachCurrentThread |

注意 `JavaVM` 和 `JNIEnv` 是不同的函数表：这里 JavaVM 的 `+0x30` 是 GetEnv，而上文 JNIEnv 的同一偏移是 FindClass。不能只按偏移、不按接收对象类型命名。

### 原指令复演和源码对照

`scripts/jni-env-scope-emulation.py` 将原 ELF PT_LOAD 映射至 Unicorn，只运行原构造/析构及这三个直接 JNIInvoke 包装器；JavaVM 表指向本地合成 ABI stub。所有未声明的目标和 syscall 被阻断，不执行宿主 Java/Android。每个阶段最多 200000 条指令。

六个场景均 PASS：

| 场景 | GetEnv / Attach 返回 | 输出 env / ownership | JNI 调用序列 |
|---|---|---|---|
| null VM | 不调用 | null / 0 | 无 |
| 已附加 | 0 / 不调用 | 合成 env / 0 | GetEnv |
| 未附加，附加成功 | -2 / 0 | 合成 env / 1 | GetEnv → Attach → Detach |
| 未附加，附加失败 | -2 / -1 | null / 0 | GetEnv → Attach |
| 版本不支持 | -3 / 不调用 | null / 0 | GetEnv |
| 其它 GetEnv 错误 | -1 / 不调用 | null / 0 | GetEnv |

合成 stub 故意在错误返回时也向输出参数写入非空 env，确认原构造函数的失败分支会主动归零。它也对 GetEnv 的版本、Attach 的 null args、对象地址与输出槽地址作断言。完整字段和调用轨迹在 `evidence/jni-env-scope-emulation.json`。

`src/accessibility_env.hpp/.cpp` 实现 `prism::accessibility::ScopedJniEnvironment(JavaVM*)`，提供 `get()`，禁止复制/移动，按上述原行为管理附加所有权。它要求创建、使用、销毁发生在同一 native 线程；不拥有 JavaVM 的生存期，不自行销毁 JVM。

`tests/jni_env_tests.cpp` 用 C++ JavaVM 表复测同六场景，并以 `offsetof(JNIInvokeInterface, ...)` 验证 3 个 VM 表槽位。执行：

```powershell
& 'D:\PrismSUN\research\accessibility\scripts\jni-env-build.ps1'
& 'D:\Python 314\python.exe' 'D:\PrismSUN\research\accessibility\scripts\jni-env-scope-emulation.py'
```

结果：源码 host 六场景 PASS；NDK `aarch64-linux-android24`、C++17、`-Wall -Wextra -Werror` 编译 PASS；原指令六场景 PASS。新验收清单为 `evidence/jni-env-build-verification.json`，产物 `build/accessibility_env.o`。先前的 8 个枚举 adapter 测试未被修改或重跑。

环境生命周期的函数语义已确认；真实 singleton 的 JavaVM 何时赋值、Android 上的 VM 返回结果、线程归属等仍是现场运行条件，不把合成执行称为设备实测。
