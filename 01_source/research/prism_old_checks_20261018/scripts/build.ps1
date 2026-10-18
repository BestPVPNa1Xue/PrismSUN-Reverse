param(
 [string]$HostCompiler='D:\msys64\ucrt64\bin\g++.exe',
 [string]$Ndk='C:\Users\ASUS\AppData\Local\Android\Sdk\ndk\27.0.12077973'
)
$ErrorActionPreference='Stop'
$projectRoot=Split-Path -Parent $PSScriptRoot
$savedPath=$env:PATH
Push-Location $projectRoot
try {
 $env:PATH=(Split-Path -Parent $HostCompiler)+';'+$env:PATH
 New-Item -ItemType Directory -Force build | Out-Null
 $flags=@('-std=c++17','-O2','-Wall','-Wextra','-Werror')
 & $HostCompiler @flags src/checks.cpp tests/core.cpp -o build/core.exe
 if($LASTEXITCODE){throw 'Core build failed'}
 & ./build/core.exe | Tee-Object build/core-tests.json
 if($LASTEXITCODE){throw 'Core tests failed'}
 $sysroot=Join-Path $Ndk 'toolchains/llvm/prebuilt/windows-x86_64/sysroot'
 & $HostCompiler @flags '-idirafter' "$sysroot/usr/include" src/xposed.cpp tests/jni.cpp -o build/jni.exe
 if($LASTEXITCODE){throw 'JNI build failed'}
 & ./build/jni.exe | Tee-Object build/jni-tests.json
 if($LASTEXITCODE){throw 'JNI tests failed'}
 $clang=Join-Path $Ndk 'toolchains/llvm/prebuilt/windows-x86_64/bin/clang++.exe'
 & $clang @flags '--target=aarch64-linux-android24' '-static-libstdc++' '-shared' '-fPIC' src/checks.cpp src/xposed.cpp src/native.cpp '-Wl,--no-undefined' -o build/libprism_old_checks.so
 if($LASTEXITCODE){throw 'Android build failed'}
 @{status='PASS';host='core and synthetic JNI executed';android='aarch64-linux-android24 cross compilation only';flags=$flags;outputs=@(Get-ChildItem build -File | Get-FileHash -Algorithm SHA256 | Select-Object Path,Hash)} | ConvertTo-Json -Depth 4 | Set-Content build/build.json
} finally {Pop-Location;$env:PATH=$savedPath}
