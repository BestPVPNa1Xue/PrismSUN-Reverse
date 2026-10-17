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
$savedPath=$env:PATH
try {
  $env:PATH=(Split-Path -Parent $HostCompiler)+';'+$env:PATH
  $sysroot=Join-Path $Ndk 'toolchains/llvm/prebuilt/windows-x86_64/sysroot'
  $sources=@((Join-Path $projectRoot 'src/detection_chains.cpp'),(Join-Path $researchRoot 'environment_memory/src/environment_memory.cpp'),(Join-Path $researchRoot 'src/observed_models.cpp'))
  $jniSources=@((Join-Path $projectRoot 'src/classes_jni.cpp'),(Join-Path $researchRoot 'accessibility/src/accessibility_env.cpp'))
  $common=@('-std=c++17','-O2','-Wall','-Wextra','-Werror')
  & $HostCompiler @common @sources (Join-Path $projectRoot 'tests/unit_tests.cpp') '-o' (Join-Path $hostDir 'unit_tests.exe')
  if($LASTEXITCODE -ne 0){throw 'Host core compile failed'}
  & $HostCompiler @common '-idirafter' (Join-Path $sysroot 'usr/include') @sources @jniSources (Join-Path $projectRoot 'tests/jni_tests.cpp') '-o' (Join-Path $hostDir 'jni_tests.exe')
  if($LASTEXITCODE -ne 0){throw 'Host JNI compile failed'}
  $result=& (Join-Path $hostDir 'unit_tests.exe')
  if($LASTEXITCODE -ne 0){throw 'Host core tests failed'}
  $result | Set-Content -Encoding utf8 (Join-Path $projectRoot 'evidence/host-tests.json')
  $jniResult=& (Join-Path $hostDir 'jni_tests.exe')
  if($LASTEXITCODE -ne 0){throw 'Host JNI tests failed'}
  $jniResult | Set-Content -Encoding utf8 (Join-Path $projectRoot 'evidence/jni-tests.json')
  $clang=Join-Path $Ndk 'toolchains/llvm/prebuilt/windows-x86_64/bin/clang++.exe'
  & $clang @common '--target=aarch64-linux-android24' '-static-libstdc++' '-shared' '-fPIC' @sources @jniSources (Join-Path $projectRoot 'src/android_collectors.cpp') '-Wl,--no-undefined' '-o' (Join-Path $androidDir 'libprism_chains.so')
  if($LASTEXITCODE -ne 0){throw 'Android ARM64 library compile failed'}
  & $clang @common '--target=aarch64-linux-android24' '-static-libstdc++' @sources (Join-Path $projectRoot 'tests/unit_tests.cpp') '-o' (Join-Path $androidDir 'unit_tests')
  if($LASTEXITCODE -ne 0){throw 'Android test compile failed'}
  & $clang @common '--target=aarch64-linux-android24' '-static-libstdc++' @sources @jniSources (Join-Path $projectRoot 'tests/jni_tests.cpp') '-o' (Join-Path $androidDir 'jni_tests')
  if($LASTEXITCODE -ne 0){throw 'Android JNI test compile failed'}
  $outputs=Get-ChildItem -File $hostDir,$androidDir | Get-FileHash -Algorithm SHA256 | Select-Object Path,Hash
  @{hostCompiler=$HostCompiler;ndk=$Ndk;flags=$common;androidTarget='aarch64-linux-android24';outputs=$outputs;runtime='Host tests only. Android artifacts cross-compiled, not executed. No original sample execution.'} | ConvertTo-Json -Depth 6 | Set-Content -Encoding utf8 (Join-Path $projectRoot 'evidence/build.json')
  Write-Output $result
  Write-Output $jniResult
  Write-Output 'PASS: host tests executed; Android library/tests compiled only'
} finally { $env:PATH=$savedPath }
