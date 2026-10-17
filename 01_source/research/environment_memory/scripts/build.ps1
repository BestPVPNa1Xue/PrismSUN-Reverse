param(
  [string]$HostCompiler='D:\msys64\ucrt64\bin\g++.exe',
  [string]$Ndk='C:\Users\ASUS\AppData\Local\Android\Sdk\ndk\27.0.12077973'
)
$ErrorActionPreference='Stop'
$projectRoot=Split-Path -Parent $PSScriptRoot
$researchRoot=Split-Path -Parent $projectRoot
$hostDir=Join-Path $projectRoot 'build/host'
$androidDir=Join-Path $projectRoot 'build/android-arm64'
New-Item -ItemType Directory -Force -Path $hostDir,$androidDir | Out-Null
$env:PATH=(Split-Path -Parent $HostCompiler)+';'+$env:PATH
$sysroot=Join-Path $Ndk 'toolchains/llvm/prebuilt/windows-x86_64/sysroot'
$sources=@((Join-Path $projectRoot 'src/environment_memory.cpp'),(Join-Path $researchRoot 'src/observed_models.cpp'),(Join-Path $researchRoot 'src/class_probe_model.cpp'))
$jniSources=@((Join-Path $projectRoot 'src/input_methods_jni.cpp'),(Join-Path $researchRoot 'accessibility/src/accessibility_env.cpp'))
$common=@('-std=c++17','-O2','-Wall','-Wextra','-Werror',('-I'+(Join-Path $projectRoot 'src')),('-I'+(Join-Path $researchRoot 'src')))
& $HostCompiler @common @sources (Join-Path $projectRoot 'tests/unit_tests.cpp') '-o' (Join-Path $hostDir 'unit_tests.exe')
if($LASTEXITCODE -ne 0){throw 'Host test compile failed'}
& $HostCompiler @common @sources (Join-Path $projectRoot 'src/main.cpp') '-o' (Join-Path $hostDir 'prism_environment.exe')
if($LASTEXITCODE -ne 0){throw 'Host executable compile failed'}
& $HostCompiler @common '-idirafter' (Join-Path $sysroot 'usr/include') @sources @jniSources '-shared' '-Wl,--export-all-symbols' '-o' (Join-Path $hostDir 'prism_environment.dll')
if($LASTEXITCODE -ne 0){throw 'Host shared library compile failed'}
& $HostCompiler @common '-idirafter' (Join-Path $sysroot 'usr/include') @jniSources (Join-Path $projectRoot 'tests/jni_adapter_tests.cpp') '-o' (Join-Path $hostDir 'jni_adapter_tests.exe')
if($LASTEXITCODE -ne 0){throw 'JNI adapter test compile failed'}
$clang=Join-Path $Ndk 'toolchains/llvm/prebuilt/windows-x86_64/bin/clang++.exe'
& $clang @common '--target=aarch64-linux-android24' '-static-libstdc++' @sources (Join-Path $projectRoot 'src/main.cpp') '-o' (Join-Path $androidDir 'prism_environment')
if($LASTEXITCODE -ne 0){throw 'Android executable compile failed'}
& $clang @common '--target=aarch64-linux-android24' '-static-libstdc++' '-shared' '-fPIC' @sources @jniSources '-o' (Join-Path $androidDir 'libprism_environment.so')
if($LASTEXITCODE -ne 0){throw 'Android shared library compile failed'}
$result=& (Join-Path $hostDir 'unit_tests.exe')
if($LASTEXITCODE -ne 0){throw 'Host tests failed'}
$result | Set-Content -Encoding utf8 (Join-Path $projectRoot 'evidence/host-tests.json')
$jniResult=& (Join-Path $hostDir 'jni_adapter_tests.exe')
if($LASTEXITCODE -ne 0){throw 'JNI adapter tests failed'}
$jniResult | Set-Content -Encoding utf8 (Join-Path $projectRoot 'evidence/jni-tests.json')
$outputs=Get-ChildItem -File $hostDir,$androidDir | Get-FileHash -Algorithm SHA256 | Select-Object Path,Hash
@{hostCompiler=$HostCompiler;ndk=$Ndk;flags=$common;androidTarget='aarch64-linux-android24';outputs=$outputs;runtime='Windows tests executed; Android compiled only'} | ConvertTo-Json -Depth 6 | Set-Content -Encoding utf8 (Join-Path $projectRoot 'evidence/build.json')
Write-Output $result
Write-Output $jniResult
Write-Output 'PASS: Windows EXE/DLL and Android ARM64 executable/SO built'
