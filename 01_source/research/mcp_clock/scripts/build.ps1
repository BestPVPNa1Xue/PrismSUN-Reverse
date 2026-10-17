param(
 [string]$HostCompiler='D:\msys64\ucrt64\bin\g++.exe',
 [string]$Ndk='C:\Users\ASUS\AppData\Local\Android\Sdk\ndk\27.0.12077973'
)
$ErrorActionPreference='Stop'
$projectRoot=Split-Path -Parent $PSScriptRoot
$hostDir=Join-Path $projectRoot 'build\host'
$androidDir=Join-Path $projectRoot 'build\android-arm64'
New-Item -ItemType Directory -Force -Path $hostDir,$androidDir | Out-Null
$env:PATH=(Split-Path -Parent $HostCompiler)+';'+$env:PATH
$common=@('-std=c++17','-O2','-Wall','-Wextra','-Werror','-I'+(Join-Path $projectRoot 'src'))
$sources=@('mcp_chain.cpp','clock_chain.cpp','crypto.cpp') | ForEach-Object {Join-Path $projectRoot ('src\'+$_)}
& $HostCompiler @common @sources (Join-Path $projectRoot 'src\main.cpp') '-lbcrypt' '-static-libgcc' '-static-libstdc++' '-o' (Join-Path $hostDir 'prism_mcp_clock.exe')
if($LASTEXITCODE -ne 0){throw 'Host CLI compile failed'}
& $HostCompiler @common @sources (Join-Path $projectRoot 'tests\unit_tests.cpp') '-lbcrypt' '-static-libgcc' '-static-libstdc++' '-o' (Join-Path $hostDir 'unit_tests.exe')
if($LASTEXITCODE -ne 0){throw 'Host tests compile failed'}
$testOutput=& (Join-Path $hostDir 'unit_tests.exe')
if($LASTEXITCODE -ne 0){throw 'Host tests failed'}
$testOutput | Set-Content -LiteralPath (Join-Path $projectRoot 'evidence\unit-tests.txt') -Encoding utf8
Write-Output $testOutput
$clang=Join-Path $Ndk 'toolchains\llvm\prebuilt\windows-x86_64\bin\clang++.exe'
$android=@('--target=aarch64-linux-android24','-static-libstdc++')
& $clang @common @android @sources (Join-Path $projectRoot 'src\main.cpp') '-o' (Join-Path $androidDir 'prism_mcp_clock')
if($LASTEXITCODE -ne 0){throw 'Android CLI compile failed'}
& $clang @common @android '-shared' '-fPIC' (Join-Path $projectRoot 'src\mcp_chain.cpp') '-o' (Join-Path $androidDir 'libprism_mcp_chain.so')
if($LASTEXITCODE -ne 0){throw 'Android MCP library compile failed'}
& $clang @common @android '-shared' '-fPIC' (Join-Path $projectRoot 'src\clock_chain.cpp') (Join-Path $projectRoot 'src\crypto.cpp') '-o' (Join-Path $androidDir 'libprism_clock_chain.so')
if($LASTEXITCODE -ne 0){throw 'Android clock library compile failed'}
& $clang @common @android @sources (Join-Path $projectRoot 'tests\unit_tests.cpp') '-o' (Join-Path $androidDir 'unit_tests')
if($LASTEXITCODE -ne 0){throw 'Android tests compile failed'}
@{hostCompiler=$HostCompiler;ndk=$Ndk;flags=$common;androidTarget='aarch64-linux-android24';hostTest=$testOutput;androidExecuted=$false;outputs=@(Get-ChildItem $hostDir,$androidDir -File | Get-FileHash -Algorithm SHA256 | Select-Object Path,Hash)} | ConvertTo-Json -Depth 6 | Set-Content -LiteralPath (Join-Path $projectRoot 'evidence\build.json') -Encoding utf8
Write-Output 'PASS: Windows CLI/tests; Android arm64 CLI/tests and two shared libraries'
