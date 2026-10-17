param(
    [string]$NdkRoot = '',
    [string]$OutputDirectory = ''
)

$ErrorActionPreference = 'Stop'
$researchRoot = Split-Path -Parent $PSScriptRoot
$workspaceRoot = Split-Path -Parent $researchRoot

if ([string]::IsNullOrWhiteSpace($NdkRoot)) {
    foreach ($candidate in @($env:ANDROID_NDK_HOME, $env:ANDROID_NDK_ROOT, $env:NDK_HOME)) {
        if (-not [string]::IsNullOrWhiteSpace($candidate) -and (Test-Path -LiteralPath $candidate)) {
            $NdkRoot = $candidate
            break
        }
    }
}
if ([string]::IsNullOrWhiteSpace($NdkRoot)) {
    foreach ($sdkRoot in @($env:ANDROID_SDK_ROOT, $env:ANDROID_HOME,
        $(if ($env:LOCALAPPDATA) { Join-Path $env:LOCALAPPDATA 'Android\Sdk' }))) {
        if ([string]::IsNullOrWhiteSpace($sdkRoot)) { continue }
        $ndkDirectory = Join-Path $sdkRoot 'ndk'
        if (Test-Path -LiteralPath $ndkDirectory) {
            $latest = Get-ChildItem -LiteralPath $ndkDirectory -Directory |
                Sort-Object Name -Descending | Select-Object -First 1
            if ($latest) { $NdkRoot = $latest.FullName; break }
        }
    }
}
if ([string]::IsNullOrWhiteSpace($NdkRoot) -or -not (Test-Path -LiteralPath $NdkRoot)) {
    throw 'Android NDK not found. Pass -NdkRoot or set ANDROID_NDK_HOME.'
}

$prebuiltNames = if ($IsWindows -or $env:OS -eq 'Windows_NT') {
    @('windows-x86_64')
} elseif ($IsMacOS) {
    @('darwin-arm64', 'darwin-x86_64')
} else {
    @('linux-x86_64')
}
$toolchain = $null
foreach ($prebuilt in $prebuiltNames) {
    $candidate = Join-Path $NdkRoot "toolchains\llvm\prebuilt\$prebuilt"
    if (Test-Path -LiteralPath $candidate) { $toolchain = $candidate; break }
}
if (-not $toolchain) { throw "No supported LLVM prebuilt directory found under: $NdkRoot" }
$compilerName = if ($IsWindows -or $env:OS -eq 'Windows_NT') { 'clang++.exe' } else { 'clang++' }
$compiler = Join-Path $toolchain "bin\$compilerName"
if (-not (Test-Path -LiteralPath $compiler)) { throw "NDK C++ compiler not found: $compiler" }

if ([string]::IsNullOrWhiteSpace($OutputDirectory)) {
    $OutputDirectory = Join-Path $researchRoot 'build\aggregate-android-arm64'
}
$OutputDirectory = [System.IO.Path]::GetFullPath($OutputDirectory)
New-Item -ItemType Directory -Force -Path $OutputDirectory | Out-Null
$output = Join-Path $OutputDirectory 'libprismsun_reconstruction.so'

$classifiedModelRoot = Join-Path $researchRoot 'detection_points'
function Resolve-PointSource([string]$category, [string]$name) {
    $classified = Join-Path $classifiedModelRoot (Join-Path $category (Join-Path 'src' $name))
    if (Test-Path -LiteralPath $classified) { return $classified }
    $legacyDirectory = switch ($category) {
        'accessibility' { 'accessibility\src' }
        'device_identity' { 'device_identity\src' }
        'environment_memory' { 'environment_memory\src' }
        'proc_fd_clock_mcp' { 'mcp_clock\src' }
        default { 'src' }
    }
    # Backward-compatible lookup when building in the original research tree.
    return (Join-Path (Join-Path $researchRoot $legacyDirectory) $name)
}
function Resolve-PointDirectory([string]$category) {
    $classified = Join-Path $classifiedModelRoot (Join-Path $category 'src')
    if (Test-Path -LiteralPath $classified) { return $classified }
    switch ($category) {
        'accessibility' { return (Join-Path $researchRoot 'accessibility\src') }
        'device_identity' { return (Join-Path $researchRoot 'device_identity\src') }
        'environment_memory' { return (Join-Path $researchRoot 'environment_memory\src') }
        'proc_fd_clock_mcp' { return (Join-Path $researchRoot 'mcp_clock\src') }
        default { return (Join-Path $researchRoot 'src') }
    }
}
$sourcePaths = @(
    (Resolve-PointSource 'aarch64_entry_classifier' 'verified_helpers.cpp')
    (Resolve-PointSource 'tracer_filter_policy' 'observed_models.cpp')
    (Resolve-PointSource 'shared_ring_reader' 'shared_ring_model.cpp')
    (Resolve-PointSource 'jni_class_probe' 'class_probe_model.cpp')
    (Resolve-PointSource 'accessibility' 'accessibility_core.cpp')
    (Resolve-PointSource 'accessibility' 'accessibility_jni.cpp')
    (Resolve-PointSource 'accessibility' 'accessibility_env.cpp')
    (Resolve-PointSource 'accessibility' 'accessibility_monitor.cpp')
    (Resolve-PointSource 'device_identity' 'crypto.cpp')
    (Resolve-PointSource 'device_identity' 'identity.cpp')
    (Resolve-PointSource 'device_identity' 'android_adapter.cpp')
    (Resolve-PointSource 'environment_memory' 'environment_memory.cpp')
    (Resolve-PointSource 'environment_memory' 'input_methods_jni.cpp')
    (Resolve-PointSource 'proc_fd_clock_mcp' 'mcp_chain.cpp')
    (Resolve-PointSource 'proc_fd_clock_mcp' 'clock_chain.cpp')
    (Resolve-PointSource 'proc_fd_clock_mcp' 'crypto.cpp')
    (Resolve-PointSource 'jni_class_probe' 'jni_layout_check.cpp')
)
foreach ($source in $sourcePaths) {
    if (-not (Test-Path -LiteralPath $source)) { throw "Required source is missing: $source" }
}

$includePaths = @(
    (Resolve-PointDirectory 'aarch64_entry_classifier'),
    (Resolve-PointDirectory 'tracer_filter_policy'),
    (Resolve-PointDirectory 'shared_ring_reader'),
    (Resolve-PointDirectory 'jni_class_probe'),
    (Resolve-PointDirectory 'accessibility'),
    (Resolve-PointDirectory 'device_identity'),
    (Resolve-PointDirectory 'environment_memory'),
    (Resolve-PointDirectory 'proc_fd_clock_mcp')
) | ForEach-Object { '-I' + $_ }
$flags = @(
    '--target=aarch64-linux-android24',
    '-std=c++17', '-O2', '-Wall', '-Wextra', '-Werror',
    '-fPIC', '-shared', '-static-libstdc++', '-Wl,--no-undefined'
)

Write-Output "NDK: $NdkRoot"
Write-Output "Compiler: $compiler"
Write-Output "Compiling $($sourcePaths.Count) implementation/validation translation units for Android arm64 API 24..."
& $compiler @flags @includePaths @sourcePaths '-ldl' '-o' $output
if ($LASTEXITCODE -ne 0) { throw "Aggregate Android shared-library build failed (exit $LASTEXITCODE)." }

$readelf = Join-Path $toolchain "bin\llvm-readelf$(if ($IsWindows -or $env:OS -eq 'Windows_NT') { '.exe' })"
$elfHeader = $null
if (Test-Path -LiteralPath $readelf) {
    $elfHeader = & $readelf -h $output | Select-String -Pattern 'Class:|Machine:|Type:' | ForEach-Object { $_.Line.Trim() }
    if ($LASTEXITCODE -ne 0) { throw 'llvm-readelf failed to inspect the generated shared library.' }
    if (($elfHeader -join ' ') -notmatch 'ELF64' -or ($elfHeader -join ' ') -notmatch 'AArch64') {
        throw "Unexpected output architecture: $($elfHeader -join '; ')"
    }
}

$manifest = [ordered]@{
    target = 'aarch64-linux-android24'
    scope = 'Combined semantic reconstruction modules; not a drop-in replacement for the original plugin'
    compiler = (& $compiler --version | Select-Object -First 1)
    source_count = $sourcePaths.Count
    flags = $flags
    output = [ordered]@{
        path = $output
        size = (Get-Item -LiteralPath $output).Length
        sha256 = (Get-FileHash -LiteralPath $output -Algorithm SHA256).Hash.ToLowerInvariant()
    }
    sources = @($sourcePaths | ForEach-Object {
        [ordered]@{
            path = $_.Substring($researchRoot.Length + 1).Replace('\', '/')
            sha256 = (Get-FileHash -LiteralPath $_ -Algorithm SHA256).Hash.ToLowerInvariant()
        }
    })
    elf_header = $elfHeader
}
$manifestPath = Join-Path $OutputDirectory 'build-manifest.json'
$manifest | ConvertTo-Json -Depth 6 | Set-Content -LiteralPath $manifestPath -Encoding utf8
Write-Output "PASS: $output"
Write-Output "SHA-256: $($manifest.output.sha256)"
