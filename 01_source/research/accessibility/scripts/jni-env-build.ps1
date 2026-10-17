$ErrorActionPreference = 'Stop'
$root = Split-Path -Parent $PSScriptRoot
$hostCxx = 'D:\msys64\ucrt64\bin\clang++.exe'
$ndkRoot = 'C:\Users\ASUS\AppData\Local\Android\Sdk\ndk\27.0.12077973\toolchains\llvm\prebuilt\windows-x86_64'
$ndkCxx = Join-Path $ndkRoot 'bin\clang++.exe'
$env:PATH = (Split-Path -Parent $hostCxx) + ';' + $env:PATH
$source = Join-Path $root 'src\accessibility_env.cpp'
$test = Join-Path $root 'tests\jni_env_tests.cpp'
$exe = Join-Path $root 'build\jni_env_tests.exe'
$object = Join-Path $root 'build\accessibility_env.o'
& $hostCxx -std=c++17 -O2 -Wall -Wextra -Werror -idirafter (Join-Path $ndkRoot 'sysroot\usr\include') $source $test -o $exe
if ($LASTEXITCODE -ne 0) { throw 'JNI env-scope host compilation failed' }
$testOutput = & $exe
if ($LASTEXITCODE -ne 0) { throw 'JNI env-scope test failed' }
& $ndkCxx --target=aarch64-linux-android24 -std=c++17 -O2 -Wall -Wextra -Werror -fPIC -c $source -o $object
if ($LASTEXITCODE -ne 0) { throw 'JNI env-scope Android compilation failed' }
$result = [ordered]@{
    scope = 'Original env lifecycle reconstruction; fake JavaVM and ARM64 emulation agreement, no device runtime'
    android_target = 'aarch64-linux-android24'
    tests = $testOutput
    status = 'PASS'
    files = @($source, (Join-Path $root 'src\accessibility_env.hpp'), $test, $exe, $object) | ForEach-Object {
        [ordered]@{path=$_; sha256=(Get-FileHash -LiteralPath $_ -Algorithm SHA256).Hash.ToLowerInvariant(); size=(Get-Item -LiteralPath $_).Length}
    }
}
$result | ConvertTo-Json -Depth 8 | Set-Content -LiteralPath (Join-Path $root 'evidence\jni-env-build-verification.json') -Encoding utf8
$testOutput
