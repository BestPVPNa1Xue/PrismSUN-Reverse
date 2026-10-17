$ErrorActionPreference = 'Stop'
$root = Split-Path -Parent $PSScriptRoot
$hostCxx = 'D:\msys64\ucrt64\bin\clang++.exe'
$ndkCxx = 'C:\Users\ASUS\AppData\Local\Android\Sdk\ndk\27.0.12077973\toolchains\llvm\prebuilt\windows-x86_64\bin\clang++.exe'
$source = Join-Path $root 'src\class_probe_model.cpp'
$header = Join-Path $root 'src\class_probe_model.h'
$layout = Join-Path $root 'src\jni_layout_check.cpp'
$dll = Join-Path $root 'build\host\prism_class_probe.dll'
$androidLibrary = Join-Path $root 'build\android-arm64\libprism_class_probe.so'
$layoutObject = Join-Path $root 'build\android-arm64\jni_layout_check.o'
$inputTime = @($source, $header) | ForEach-Object { (Get-Item -LiteralPath $_).LastWriteTimeUtc } | Sort-Object -Descending | Select-Object -First 1
if (!(Test-Path -LiteralPath $dll) -or (Get-Item -LiteralPath $dll).LastWriteTimeUtc -lt $inputTime) {
    & $hostCxx -std=c++17 -O2 -Wall -Wextra -Werror -shared -static-libgcc -static-libstdc++ $source -o $dll
    if ($LASTEXITCODE -ne 0) { throw 'Host class probe model build failed' }
} else {
    Write-Output 'Existing host class probe model is current; build skipped.'
}
if (!(Test-Path -LiteralPath $androidLibrary) -or (Get-Item -LiteralPath $androidLibrary).LastWriteTimeUtc -lt $inputTime) {
    & $ndkCxx --target=aarch64-linux-android24 -std=c++17 -O2 -Wall -Wextra -Werror -shared -fPIC -fvisibility=hidden -nostdlib++ $source -o $androidLibrary
    if ($LASTEXITCODE -ne 0) { throw 'Android class probe model build failed' }
} else {
    Write-Output 'Existing Android class probe model is current; build skipped.'
}
if (!(Test-Path -LiteralPath $layoutObject) -or (Get-Item -LiteralPath $layoutObject).LastWriteTimeUtc -lt (Get-Item -LiteralPath $layout).LastWriteTimeUtc) {
    & $ndkCxx --target=aarch64-linux-android24 -std=c++17 -Wall -Wextra -Werror -c $layout -o $layoutObject
    if ($LASTEXITCODE -ne 0) { throw 'JNI table offset assertions failed' }
} else {
    Write-Output 'Existing JNI layout assertions are current; build skipped.'
}
$manifest = [ordered]@{
    scope = 'Event 22 class-list selection control flow with external JNI and container dependencies'
    host_compiler = (& $hostCxx --version | Select-Object -First 1)
    android_compiler = (& $ndkCxx --version | Select-Object -First 1)
    android_target = 'aarch64-linux-android24'
    jni_offsets = [ordered]@{FindClass = 48; ExceptionCheck = 1824; ExceptionClear = 136; DeleteLocalRef = 184}
    files = @($source, $header, $layout, $dll, $androidLibrary, $layoutObject) | ForEach-Object {
        $item = Get-Item -LiteralPath $_
        [ordered]@{path = $_; size = $item.Length; sha256 = (Get-FileHash -LiteralPath $_ -Algorithm SHA256).Hash.ToLowerInvariant()}
    }
}
$manifest | ConvertTo-Json -Depth 6 | Set-Content -LiteralPath (Join-Path $root 'evidence\build_class_probe.json') -Encoding utf8
Write-Output 'Class probe model and JNI layout assertions build complete.'
