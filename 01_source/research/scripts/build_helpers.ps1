$ErrorActionPreference = 'Stop'
$root = Split-Path -Parent $PSScriptRoot
$hostOut = Join-Path $root 'build\host'
$androidOut = Join-Path $root 'build\android-arm64'
New-Item -ItemType Directory -Path $hostOut, $androidOut -Force | Out-Null
$hostCxx = 'D:\msys64\ucrt64\bin\clang++.exe'
$env:PATH = (Split-Path -Parent $hostCxx) + ';' + $env:PATH
$ndkCxx = 'C:\Users\ASUS\AppData\Local\Android\Sdk\ndk\27.0.12077973\toolchains\llvm\prebuilt\windows-x86_64\bin\clang++.exe'
$source = Join-Path $root 'src\verified_helpers.cpp'
$test = Join-Path $root 'src\test_helpers.cpp'
$dll = Join-Path $hostOut 'prism_helpers.dll'
$exe = Join-Path $hostOut 'test_helpers.exe'
$androidLibrary = Join-Path $androidOut 'libprism_helpers.so'
& $hostCxx -std=c++17 -O2 -Wall -Wextra -Werror -shared -static-libgcc -static-libstdc++ $source -o $dll
if ($LASTEXITCODE -ne 0) { throw 'Host library build failed' }
& $hostCxx -std=c++17 -O2 -Wall -Wextra -Werror -static-libgcc -static-libstdc++ $source $test -o $exe
if ($LASTEXITCODE -ne 0) { throw 'Host test build failed' }
& $exe
if ($LASTEXITCODE -ne 0) { throw 'Host tests failed' }
& $ndkCxx --target=aarch64-linux-android24 -std=c++17 -O2 -Wall -Wextra -Werror -shared -fPIC -fvisibility=hidden -nostdlib++ $source -o $androidLibrary
if ($LASTEXITCODE -ne 0) { throw 'Android helper build failed' }
$manifest = [ordered]@{
    scope = 'Verified helper bodies, not a drop-in replacement for libprism-sun.so'
    host_compiler = (& $hostCxx --version | Select-Object -First 1)
    android_compiler = (& $ndkCxx --version | Select-Object -First 1)
    android_target = 'aarch64-linux-android24'
    files = @($source, (Join-Path $root 'src\verified_helpers.h'), $dll, $exe, $androidLibrary) | ForEach-Object {
        $item = Get-Item -LiteralPath $_
        [ordered]@{path = $_; size = $item.Length; sha256 = (Get-FileHash -LiteralPath $_ -Algorithm SHA256).Hash.ToLowerInvariant()}
    }
}
$manifest | ConvertTo-Json -Depth 6 | Set-Content -LiteralPath (Join-Path $root 'evidence\build_helpers.json') -Encoding utf8
Write-Output "Built $dll and $androidLibrary"
