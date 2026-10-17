$ErrorActionPreference = 'Stop'
$root = Split-Path -Parent $PSScriptRoot
$hostCxx = 'D:\msys64\ucrt64\bin\clang++.exe'
$ndkCxx = 'C:\Users\ASUS\AppData\Local\Android\Sdk\ndk\27.0.12077973\toolchains\llvm\prebuilt\windows-x86_64\bin\clang++.exe'
$source = Join-Path $root 'src\observed_models.cpp'
$header = Join-Path $root 'src\observed_models.h'
$dll = Join-Path $root 'build\host\prism_observed_models.dll'
$androidLibrary = Join-Path $root 'build\android-arm64\libprism_observed_models.so'
$inputTime = @($source, $header) | ForEach-Object { (Get-Item -LiteralPath $_).LastWriteTimeUtc } | Sort-Object -Descending | Select-Object -First 1
if (!(Test-Path -LiteralPath $dll) -or (Get-Item -LiteralPath $dll).LastWriteTimeUtc -lt $inputTime) {
    & $hostCxx -std=c++17 -O2 -Wall -Wextra -Werror -shared -static-libgcc -static-libstdc++ $source -o $dll
    if ($LASTEXITCODE -ne 0) { throw 'Host model build failed' }
} else {
    Write-Output 'Existing host model library is current; build skipped.'
}
if (!(Test-Path -LiteralPath $androidLibrary) -or (Get-Item -LiteralPath $androidLibrary).LastWriteTimeUtc -lt $inputTime) {
    & $ndkCxx --target=aarch64-linux-android24 -std=c++17 -O2 -Wall -Wextra -Werror -shared -fPIC -fvisibility=hidden -nostdlib++ $source -o $androidLibrary
    if ($LASTEXITCODE -ne 0) { throw 'Android model build failed' }
} else {
    Write-Output 'Existing Android model library is current; build skipped.'
}
$manifest = [ordered]@{
    scope = 'Three observed predicates and one flag-update model; not a replacement for the module'
    host_compiler = (& $hostCxx --version | Select-Object -First 1)
    android_compiler = (& $ndkCxx --version | Select-Object -First 1)
    android_target = 'aarch64-linux-android24'
    files = @($source, $header, $dll, $androidLibrary) | ForEach-Object {
        $item = Get-Item -LiteralPath $_
        [ordered]@{path = $_; size = $item.Length; sha256 = (Get-FileHash -LiteralPath $_ -Algorithm SHA256).Hash.ToLowerInvariant()}
    }
}
$manifest | ConvertTo-Json -Depth 6 | Set-Content -LiteralPath (Join-Path $root 'evidence\build_models.json') -Encoding utf8
Write-Output "Model artifacts verified: $dll and $androidLibrary"
