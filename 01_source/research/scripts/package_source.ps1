param(
    [string]$OutputPath = '',
    [switch]$Force
)

$ErrorActionPreference = 'Stop'
$researchRoot = Split-Path -Parent $PSScriptRoot
$workspaceRoot = Split-Path -Parent $researchRoot
if ([string]::IsNullOrWhiteSpace($OutputPath)) {
    $OutputPath = Join-Path $workspaceRoot 'dist\PrismSUN-reconstruction-source.zip'
}
$OutputPath = [System.IO.Path]::GetFullPath($OutputPath)
$researchPrefix = [System.IO.Path]::GetFullPath($researchRoot) + [System.IO.Path]::DirectorySeparatorChar
if ($OutputPath -notmatch '\.zip$') { throw 'OutputPath must have a .zip extension.' }
if ($OutputPath.StartsWith($researchPrefix, [System.StringComparison]::OrdinalIgnoreCase)) {
    throw 'Choose a package destination outside the research source tree.'
}
if ((Test-Path -LiteralPath $OutputPath) -and -not $Force) {
    throw "Package already exists; use -Force to replace it: $OutputPath"
}
$outputDirectory = Split-Path -Parent $OutputPath
New-Item -ItemType Directory -Force -Path $outputDirectory | Out-Null

# Whitelist only the aggregate library inputs. Each source point stays in its
# own directory; demos, tests, analysis scripts and evidence are never copied.
$sourceGroups = @(
    [pscustomobject]@{ Key = 'accessibility'; Source = 'accessibility\src'; Files = @(
        'accessibility_core.cpp', 'accessibility_core.hpp',
        'accessibility_env.cpp', 'accessibility_env.hpp',
        'accessibility_jni.cpp', 'accessibility_jni.hpp',
        'accessibility_monitor.cpp', 'accessibility_monitor.hpp'
    ) }
    [pscustomobject]@{ Key = 'device_identity'; Source = 'device_identity\src'; Files = @('android_adapter.cpp', 'android_adapter.hpp', 'crypto.cpp', 'identity.cpp', 'identity.hpp') }
    [pscustomobject]@{ Key = 'environment_memory'; Source = 'environment_memory\src'; Files = @('environment_memory.cpp', 'environment_memory.hpp', 'input_methods_jni.cpp', 'input_methods_jni.hpp') }
    [pscustomobject]@{ Key = 'proc_fd_clock_mcp'; Source = 'mcp_clock\src'; Files = @('clock_chain.cpp', 'clock_chain.hpp', 'crypto.cpp', 'mcp_chain.cpp', 'mcp_chain.hpp', 'sha_constants.inc') }
    [pscustomobject]@{ Key = 'aarch64_entry_classifier'; Source = 'src'; Files = @('verified_helpers.cpp', 'verified_helpers.h') }
    [pscustomobject]@{ Key = 'tracer_filter_policy'; Source = 'src'; Files = @('observed_models.cpp', 'observed_models.h') }
    [pscustomobject]@{ Key = 'shared_ring_reader'; Source = 'src'; Files = @('shared_ring_model.cpp', 'shared_ring_model.h') }
    [pscustomobject]@{ Key = 'jni_class_probe'; Source = 'src'; Files = @('class_probe_model.cpp', 'class_probe_model.h', 'jni_layout_check.cpp') }
)
$copyMap = [System.Collections.Generic.List[object]]::new()
foreach ($group in $sourceGroups) {
    $sourceDirectory = Join-Path $researchRoot $group.Source
    foreach ($name in $group.Files) {
        $copyMap.Add([pscustomobject]@{
            Source = Join-Path $sourceDirectory $name
            Destination = Join-Path (Join-Path 'research' (Join-Path 'detection_points' (Join-Path $group.Key 'src'))) $name
        })
    }
}
$copyMap.Add([pscustomobject]@{
    Source = Join-Path $researchRoot 'aggregate\CMakeLists.txt'
    Destination = 'research\aggregate\CMakeLists.txt'
})
$copyMap.Add([pscustomobject]@{
    Source = Join-Path $PSScriptRoot 'build_all_detections.ps1'
    Destination = 'research\scripts\build_all_detections.ps1'
})
$copyMap.Add([pscustomobject]@{
    Source = Join-Path $researchRoot 'build\aggregate-android-arm64\libprismsun_reconstruction.so'
    Destination = 'research\build\aggregate-android-arm64\libprismsun_reconstruction.so'
})

$reports = [ordered]@{
    'overview' = Join-Path $researchRoot 'REPORT.zh-CN.md'
    'accessibility' = Join-Path $researchRoot 'accessibility\REPORT.zh-CN.md'
    'device_identity' = Join-Path $researchRoot 'device_identity\REPORT.zh-CN.md'
    'environment_memory' = Join-Path $researchRoot 'environment_memory\REPORT.zh-CN.md'
    'mcp_clock' = Join-Path $researchRoot 'mcp_clock\REPORT.zh-CN.md'
}
foreach ($report in $reports.GetEnumerator()) {
    $copyMap.Add([pscustomobject]@{
        Source = $report.Value
        Destination = Join-Path 'reports' (Join-Path $report.Key 'REPORT.zh-CN.md')
    })
}
foreach ($entry in $copyMap) {
    if (-not (Test-Path -LiteralPath $entry.Source -PathType Leaf)) {
        throw "Required delivery input is missing: $($entry.Source)"
    }
}

$staging = Join-Path ([System.IO.Path]::GetTempPath()) ('PrismSUN-delivery-' + [guid]::NewGuid().ToString('N'))
$bundleRoot = Join-Path $staging 'PrismSUN-reconstruction-source'
New-Item -ItemType Directory -Force -Path $bundleRoot | Out-Null
try {
    $readme = @'
# PrismSUN 检测点重建源码交付包

本包只交付可构建源码、最终研究报告、最终聚合 Android ARM64 SO 和构建入口。源文件按检测点分类；不含原始样本、IDA 数据库、反编译快照、中间证据、测试夹具、分析脚本或旧交付包。

## 分类

| 目录 | 内容 |
| --- | --- |
| `research/detection_points/accessibility/src/` | 无障碍服务枚举、JNI 适配和变化状态机 |
| `research/detection_points/device_identity/src/` | 设备身份、客户端属性语义模型、密码与 Android 适配 |
| `research/detection_points/environment_memory/src/` | 内存完整性、环境循环和输入法 JNI 模型 |
| `research/detection_points/proc_fd_clock_mcp/src/` | MCP 文件扫描及时间/随机数消费链 |
| `research/detection_points/aarch64_entry_classifier/src/` | AArch64 入口指令分类器和字节/XOR 辅助函数 |
| `research/detection_points/tracer_filter_policy/src/` | tracer 状态与过滤器/处理器策略模型 |
| `research/detection_points/shared_ring_reader/src/` | 共享内存 ring 的稳定快照读取计划 |
| `research/detection_points/jni_class_probe/src/` | event 22 类探测模型及 JNI 布局验证 |
| `reports/` | 总报告及各专项最终报告 |
| `research/build/aggregate-android-arm64/` | 最终聚合库 `libprismsun_reconstruction.so` |

共享模型分类是聚合工程的公共源码，不代表单一运行中的检测线程。每个专项依旧是有界语义重建；报告中的未闭合项与适配差异继续有效。

## 重建边界

聚合库目标为 Android `arm64-v8a` / API 24。它把列出的模块编译到同一 SO，但不恢复原插件 ABI、完整宿主调度、网络/服务端链，也没有作为游戏客户端插件部署或运行。不能将其视为原始库的替代品。

## 重新构建

安装 Android NDK 后，在解压目录运行：

```powershell
& .\research\scripts\build_all_detections.ps1 -NdkRoot 'C:\path\to\android-ndk' -OutputDirectory '.\research\build\aggregate-android-arm64'
```

也可用 Android NDK 的 CMake toolchain 配置 `research/aggregate/CMakeLists.txt`。`PACKAGE-MANIFEST.json` 列出包内每个交付文件的大小与 SHA-256。
'@
    Set-Content -LiteralPath (Join-Path $bundleRoot 'README.zh-CN.md') -Value $readme -Encoding utf8

    foreach ($entry in $copyMap) {
        $destination = Join-Path $bundleRoot $entry.Destination
        New-Item -ItemType Directory -Force -Path (Split-Path -Parent $destination) | Out-Null
        Copy-Item -LiteralPath $entry.Source -Destination $destination
    }
    $manifestEntries = @(Get-ChildItem -LiteralPath $bundleRoot -Recurse -File | ForEach-Object {
        [ordered]@{
            path = $_.FullName.Substring($bundleRoot.Length + 1).Replace('\', '/')
            size = $_.Length
            sha256 = (Get-FileHash -LiteralPath $_.FullName -Algorithm SHA256).Hash.ToLowerInvariant()
        }
    })
    [ordered]@{
        format = 2
        name = 'PrismSUN-reconstruction-source'
        description = 'Categorized buildable reconstruction source, final reports, and final aggregate Android ARM64 library.'
        target = 'aarch64-linux-android24'
        file_count = $manifestEntries.Count
        files = $manifestEntries
    } | ConvertTo-Json -Depth 6 | Set-Content -LiteralPath (Join-Path $bundleRoot 'PACKAGE-MANIFEST.json') -Encoding utf8

    if ((Test-Path -LiteralPath $OutputPath) -and $Force) { Remove-Item -LiteralPath $OutputPath -Force }
    Compress-Archive -Path $bundleRoot -DestinationPath $OutputPath -CompressionLevel Optimal

    $zip = [System.IO.Compression.ZipFile]::OpenRead($OutputPath)
    try {
        $entries = @($zip.Entries)
        $unexpected = @($entries | Where-Object {
            $_.FullName -match '(^|/)(tests?|evidence|decompiled|node_modules|__pycache__|tooling|scripts)/' -and
            $_.FullName -notmatch '^PrismSUN-reconstruction-source/research/scripts/build_all_detections\.ps1$'
        })
        if ($unexpected.Count -gt 0) { throw "Unexpected non-delivery content: $($unexpected[0].FullName)" }
        $expected = @(
            'PrismSUN-reconstruction-source/README.zh-CN.md',
            'PrismSUN-reconstruction-source/PACKAGE-MANIFEST.json',
            'PrismSUN-reconstruction-source/research/scripts/build_all_detections.ps1',
            'PrismSUN-reconstruction-source/research/build/aggregate-android-arm64/libprismsun_reconstruction.so',
            'PrismSUN-reconstruction-source/research/aggregate/CMakeLists.txt'
        )
        foreach ($name in $expected) {
            if (-not ($entries | Where-Object FullName -eq $name)) { throw "Required package entry missing: $name" }
        }
        $sourceCount = @($entries | Where-Object { $_.FullName -match '\.(c|cc|cpp|h|hh|hpp|inc)$' }).Count
        $reportCount = @($entries | Where-Object { $_.FullName -match '^PrismSUN-reconstruction-source/reports/.+REPORT\.zh-CN\.md$' }).Count
        if ($sourceCount -ne 32) { throw "Expected 32 aggregate build source/header inputs, found $sourceCount." }
        if ($reportCount -ne 5) { throw "Expected 5 final reports, found $reportCount." }
        Write-Output "PASS: delivery verified; $($entries.Count) entries, $sourceCount build inputs, $reportCount reports."
    } finally {
        $zip.Dispose()
    }
    Write-Output "Package: $OutputPath"
    Write-Output "Size: $((Get-Item -LiteralPath $OutputPath).Length) bytes"
    Write-Output "SHA-256: $((Get-FileHash -LiteralPath $OutputPath -Algorithm SHA256).Hash.ToLowerInvariant())"
} finally {
    if (Test-Path -LiteralPath $staging) { Remove-Item -LiteralPath $staging -Recurse -Force }
}
