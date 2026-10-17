param(
  [string]$HostCompiler='D:\msys64\ucrt64\bin\g++.exe',
  [string]$Ndk='C:\Users\ASUS\AppData\Local\Android\Sdk\ndk\27.0.12077973'
)
$ErrorActionPreference='Stop'
$env:PATH=(Split-Path -Parent $HostCompiler)+';'+$env:PATH
$projectRoot=Split-Path -Parent $PSScriptRoot
$hostDir=Join-Path $projectRoot 'build\host'
$androidDir=Join-Path $projectRoot 'build\android-arm64'
New-Item -ItemType Directory -Force -Path $hostDir,$androidDir | Out-Null
$sources=@((Join-Path $projectRoot 'src\crypto.cpp'),(Join-Path $projectRoot 'src\identity.cpp'))
$common=@('-std=c++17','-O2','-Wall','-Wextra','-Werror')
& $HostCompiler @common @sources (Join-Path $projectRoot 'src\main.cpp') '-o' (Join-Path $hostDir 'prism_identity.exe')
if($LASTEXITCODE -ne 0){throw 'Host compile failed'}
& $HostCompiler @common @sources ('-I'+(Join-Path $projectRoot 'src')) (Join-Path $projectRoot 'tests\unit_tests.cpp') '-o' (Join-Path $hostDir 'unit_tests.exe')
if($LASTEXITCODE -ne 0){throw 'Host tests compile failed'}
$clang=Join-Path $Ndk 'toolchains\llvm\prebuilt\windows-x86_64\bin\clang++.exe'
& $clang @common '--target=aarch64-linux-android24' '-static-libstdc++' @sources (Join-Path $projectRoot 'src\main.cpp') '-o' (Join-Path $androidDir 'prism_identity')
if($LASTEXITCODE -ne 0){throw 'Android executable compile failed'}
& $clang @common '--target=aarch64-linux-android24' '-static-libstdc++' '-shared' '-fPIC' @sources (Join-Path $projectRoot 'src\android_adapter.cpp') '-ldl' '-o' (Join-Path $androidDir 'libprism_identity.so')
if($LASTEXITCODE -ne 0){throw 'Android library compile failed'}
@{hostCompiler=$HostCompiler;ndk=$Ndk;flags=$common;androidTarget='aarch64-linux-android24';outputs=@(Get-FileHash -Algorithm SHA256 -LiteralPath (Join-Path $hostDir 'prism_identity.exe'),(Join-Path $androidDir 'prism_identity'),(Join-Path $androidDir 'libprism_identity.so') | Select-Object Path,Hash)} | ConvertTo-Json -Depth 5 | Set-Content -Encoding utf8 (Join-Path $projectRoot 'evidence\build.json')
Write-Output 'PASS: host executable, Android arm64 executable and shared library'
