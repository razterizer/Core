@echo off

REM Set up the Visual Studio C++ build environment.
set "vc_arch=amd64"
set "vc_arch_script=vcvars64.bat"
if /I "%~1" == "x86" set "vc_arch=x86"
if /I "%~1" == "x86" set "vc_arch_script=vcvars32.bat"
if /I "%~1" == "Win32" set "vc_arch=x86"
if /I "%~1" == "Win32" set "vc_arch_script=vcvars32.bat"

if defined VCINSTALLDIR goto CheckMsbuild

set "VSINSTALLDIR="
set "vswhere="

if exist "%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" set "vswhere=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
if not defined vswhere if exist "%ProgramFiles%\Microsoft Visual Studio\Installer\vswhere.exe" set "vswhere=%ProgramFiles%\Microsoft Visual Studio\Installer\vswhere.exe"
if not defined vswhere for %%i in (vswhere.exe) do set "vswhere=%%~$PATH:i"

if defined vswhere for /f "usebackq tokens=*" %%i in (`"%vswhere%" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do set "VSINSTALLDIR=%%i"

if defined VSINSTALLDIR call :TryVcVars "%VSINSTALLDIR%\VC\Auxiliary\Build\vcvarsall.bat"
if defined VCINSTALLDIR goto CheckMsbuild
if defined VSINSTALLDIR call :TryVcVars "%VSINSTALLDIR%\VC\Auxiliary\Build\%vc_arch_script%"
if defined VCINSTALLDIR goto CheckMsbuild

call :TryVcVars "%ProgramFiles%\Microsoft Visual Studio\2026\Enterprise\VC\Auxiliary\Build\vcvarsall.bat"
if defined VCINSTALLDIR goto CheckMsbuild
call :TryVcVars "%ProgramFiles%\Microsoft Visual Studio\2026\Professional\VC\Auxiliary\Build\vcvarsall.bat"
if defined VCINSTALLDIR goto CheckMsbuild
call :TryVcVars "%ProgramFiles%\Microsoft Visual Studio\2026\Community\VC\Auxiliary\Build\vcvarsall.bat"
if defined VCINSTALLDIR goto CheckMsbuild
call :TryVcVars "%ProgramFiles%\Microsoft Visual Studio\2026\BuildTools\VC\Auxiliary\Build\vcvarsall.bat"
if defined VCINSTALLDIR goto CheckMsbuild
call :TryVcVars "%ProgramFiles%\Microsoft Visual Studio\2022\Enterprise\VC\Auxiliary\Build\vcvarsall.bat"
if defined VCINSTALLDIR goto CheckMsbuild
call :TryVcVars "%ProgramFiles%\Microsoft Visual Studio\2022\Professional\VC\Auxiliary\Build\vcvarsall.bat"
if defined VCINSTALLDIR goto CheckMsbuild
call :TryVcVars "%ProgramFiles%\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat"
if defined VCINSTALLDIR goto CheckMsbuild
call :TryVcVars "%ProgramFiles%\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvarsall.bat"
if defined VCINSTALLDIR goto CheckMsbuild

echo Error: Visual Studio C++ build environment not found. Install Visual Studio or Build Tools.
exit /b 1

:CheckMsbuild
where msbuild >nul 2>nul
if errorlevel 1 (
    echo Error: msbuild not found after setting up Visual Studio environment.
    exit /b 1
)

echo Building on Windows with VC++...
exit /b 0

:TryVcVars
if not exist "%~1" exit /b 0
call %1 %vc_arch%
exit /b 0
