@echo off

REM Set up the Visual Studio environment.
set "vc_arch=x64"
if /I "%~1" == "x86" set "vc_arch=x86"
if /I "%~1" == "Win32" set "vc_arch=x86"

if not defined VCINSTALLDIR (
    set "vswhere=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
    if not exist "%vswhere%" (
        echo Error: vswhere.exe not found. Install Visual Studio or Build Tools.
        exit /b 1
    )

    for /f "usebackq tokens=*" %%i in (`"%vswhere%" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do (
        set "VSINSTALLDIR=%%i"
    )

    if not defined VSINSTALLDIR (
        echo Error: Visual Studio C++ build tools not found.
        exit /b 1
    )

    if not exist "%VSINSTALLDIR%\Common7\Tools\VsDevCmd.bat" (
        echo Error: Visual Studio developer command script not found.
        exit /b 1
    )

    call "%VSINSTALLDIR%\Common7\Tools\VsDevCmd.bat" -arch=%vc_arch% -host_arch=x64
    if errorlevel 1 exit /b %errorlevel%
)

where msbuild >nul 2>nul
if errorlevel 1 (
    echo Error: msbuild not found after setting up Visual Studio environment.
    exit /b 1
)

echo Building on Windows with VC++...
