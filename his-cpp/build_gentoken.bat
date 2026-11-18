@echo off
call "D:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat" > nul
cd /d "%~dp0"
cl /EHsc /std:c++17 /utf-8 ^
  /D CPP_JWT_USE_VENDORED_NLOHMANN_JSON ^
  /I his-c8-pharmacy ^
  /I lib-oatpp/include ^
  /I lib-mysql/include ^
  /I lib-common/include ^
  his-c8-pharmacy\gentoken.cpp ^
  /Fe:gentoken.exe ^
  /link libcrypto.lib libssl.lib ws2_32.lib ^
  /LIBPATH:out\build\x64-Debug\lib-oatpp ^
  /LIBPATH:out\build\x64-Debug\lib-common ^
  /LIBPATH:out\build\x64-Debug\lib-mysql ^
  /LIBPATH:lib-oatpp\lib64\openssl
if %ERRORLEVEL% EQU 0 (
    echo.
    echo gentoken.exe built successfully!
) else (
    echo.
    echo Build FAILED!
)
pause
