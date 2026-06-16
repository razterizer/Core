@echo off

REM Set up the Visual Studio environment.
set "vc_arch=x64"
if /I "%~1" == "x86" set "vc_arch=x86"
if /I "%~1" == "Win32" set "vc_arch=x86"

if defined VCINSTALLDIR goto CheckMsbuild

set "VSINSTALLDIR="
set "vswhere="

if exist "%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" set "vswhere=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
if not defined vswhere if exist "%ProgramFiles%\Microsoft Visual Studio\Installer\vswhere.exe" set "vswhere=%ProgramFiles%\Microsoft Visual Studio\Installer\vswhere.exe"
if not defined vswhere for %%i in (vswhere.exe) do set "vswhere=%%~$PATH:i"

if defined vswhere for /f "usebackq tokens=*" %%i in (`"%vswhere%" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do set "VSINSTALLDIR=%%i"

if defined VSINSTALLDIR if exist "%VSINSTALLDIR%\Common7\Tools\VsDevCmd.bat" call "%VSINSTALLDIR%\Common7\Tools\VsDevCmd.bat" -arch=%vc_arch% -host_arch=x64
if defined VSINSTALLDIR if errorlevel 1 exit /b %errorlevel%
if defined VCINSTALLDIR goto CheckMsbuild

call :TryVsDevCmd "%ProgramFiles%\Microsoft Visual Studio\2022\Enterprise\Common7\Tools\VsDevCmd.bat"
if defined VCINSTALLDIR goto CheckMsbuild
call :TryVsDevCmd "%ProgramFiles%\Microsoft Visual Studio\2022\Professional\Common7\Tools\VsDevCmd.bat"
if defined VCINSTALLDIR goto CheckMsbuild
call :TryVsDevCmd "%ProgramFiles%\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat"
if defined VCINSTALLDIR goto CheckMsbuild
call :TryVsDevCmd "%ProgramFiles%\Microsoft Visual Studio\2022\BuildTools\Common7\Tools\VsDevCmd.bat"
if defined VCINSTALLDIR goto CheckMsbuild
call :TryVsDevCmd "%ProgramFiles(x86)%\Microsoft Visual Studio\2022\Enterprise\Common7\Tools\VsDevCmd.bat"
if defined VCINSTALLDIR goto CheckMsbuild
call :TryVsDevCmd "%ProgramFiles(x86)%\Microsoft Visual Studio\2022\Professional\Common7\Tools\VsDevCmd.bat"
if defined VCINSTALLDIR goto CheckMsbuild
call :TryVsDevCmd "%ProgramFiles(x86)%\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat"
if defined VCINSTALLDIR goto CheckMsbuild
call :TryVsDevCmd "%ProgramFiles(x86)%\Microsoft Visual Studio\2022\BuildTools\Common7\Tools\VsDevCmd.bat"
if defined VCINSTALLDIR goto CheckMsbuild

echo Error: Visual Studio environment not found. Install Visual Studio or Build Tools.
exit /b 1

:CheckMsbuild
where msbuild >nul 2>nul
if errorlevel 1 (
    echo Error: msbuild not found after setting up Visual Studio environment.
    exit /b 1
)

echo Building on Windows with VC++...
exit /b 0

:TryVsDevCmd
if exist "%~1" call %1 -arch=%vc_arch% -host_arch=x64
exit /b 0
