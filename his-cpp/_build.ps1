$vcvarsPath = 'D:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat'
$tempFile = [System.IO.Path]::GetTempFileName() + '.bat'
@"
@echo off
call "$vcvarsPath" > nul 2>&1
set
"@ | Out-File -FilePath $tempFile -Encoding ASCII
$envVars = cmd /c $tempFile
Remove-Item $tempFile
foreach ($line in $envVars) {
    if ($line -match '^(.*?)=(.*)$') {
        [Environment]::SetEnvironmentVariable($matches[1], $matches[2], 'Process')
    }
}
$cmakePath = 'D:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe'
$srcDir = 'D:\workplace\zero-one-his2607\his-cpp'
$buildDir = 'D:\workplace\zero-one-his2607\his-cpp\out\build\x64-Debug'
# Reconfigure CMake to pick up new/deleted files
& $cmakePath -S $srcDir -B $buildDir -G Ninja 2>&1
Write-Host "=== CMake reconfigure done, starting build ==="
& $cmakePath --build $buildDir --target his-c8-dispense his-c8-pharmacy 2>&1
