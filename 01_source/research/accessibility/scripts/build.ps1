param([switch]$AndroidOnly)
$ErrorActionPreference = 'Stop'
$env:PATH = 'D:\msys64\ucrt64\bin;' + $env:PATH
$root = Split-Path -Parent $PSScriptRoot
$hostCxx = 'D:\msys64\ucrt64\bin\g++.exe'
$ndkCxx = 'C:\Users\ASUS\AppData\Local\Android\Sdk\ndk\27.0.12077973\toolchains\llvm\prebuilt\windows-x86_64\bin\clang++.exe'
$hostOut = Join-Path $root 'build\host'
$androidOut = Join-Path $root 'build\android-arm64'
New-Item -ItemType Directory -Force -Path $hostOut, $androidOut | Out-Null
$core = Join-Path $root 'src\accessibility_core.cpp'
$jni = Join-Path $root 'src\accessibility_jni.cpp'
$monitor = Join-Path $root 'src\accessibility_monitor.cpp'
$environment = Join-Path $root 'src\accessibility_env.cpp'
$demo = Join-Path $root 'src\accessibility_demo.cpp'
$dll = Join-Path $hostOut 'accessibility_core.dll'
$exe = Join-Path $hostOut 'accessibility_demo.exe'
$so = Join-Path $androidOut 'libaccessibility_reconstruction.so'
if (!$AndroidOnly) {
    & $hostCxx -std=c++17 -O2 -Wall -Wextra -Werror -shared -static-libgcc -static-libstdc++ $core -o $dll
    if ($LASTEXITCODE -ne 0) { throw 'Host DLL build failed' }
    & $hostCxx -std=c++17 -O2 -Wall -Wextra -Werror -static-libgcc -static-libstdc++ $core $demo -o $exe
    if ($LASTEXITCODE -ne 0) { throw 'Host executable build failed' }
}
& $ndkCxx --target=aarch64-linux-android24 -std=c++17 -O2 -Wall -Wextra -Werror -shared -fPIC -static-libstdc++ $core $jni $monitor $environment -o $so
if ($LASTEXITCODE -ne 0) { throw 'Android reconstruction build failed' }
$manifest = [ordered]@{
    scope = 'Accessibility enumeration, byte-exact snapshot hash and event state machine; semantic reconstruction, not original ABI'
    host_compiler = (& $hostCxx --version | Select-Object -First 1)
    android_compiler = (& $ndkCxx --version | Select-Object -First 1)
    android_target = 'aarch64-linux-android24'
    sources_and_outputs = @($core, $jni, $monitor, $environment, $demo, (Join-Path $root 'src\accessibility_core.hpp'), (Join-Path $root 'src\accessibility_jni.hpp'), (Join-Path $root 'src\accessibility_monitor.hpp'), (Join-Path $root 'src\accessibility_env.hpp'), $dll, $exe, $so) | ForEach-Object {
        [ordered]@{path = $_; size = (Get-Item -LiteralPath $_).Length; sha256 = (Get-FileHash -LiteralPath $_ -Algorithm SHA256).Hash.ToLowerInvariant()}
    }
}
$manifest | ConvertTo-Json -Depth 6 | Set-Content -LiteralPath (Join-Path $root 'evidence\build.json') -Encoding utf8
$env:PATH = 'D:\msys64\ucrt64\bin;' + $env:PATH
& $exe 'TARGET/.ServiceB' 'TARGET/.ServiceA'
if ($LASTEXITCODE -ne 0) { throw 'Host demonstration failed' }
