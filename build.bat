@echo off

REM Locate MSBuild from Visual Studio without invoking VsDevCmd/vcvars.
if not "%VSINSTALLDIR%" == "" goto AddMsbuildToPath

set "vswhere="
if exist "%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" set "vswhere=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
if not defined vswhere if exist "%ProgramFiles%\Microsoft Visual Studio\Installer\vswhere.exe" set "vswhere=%ProgramFiles%\Microsoft Visual Studio\Installer\vswhere.exe"
if not defined vswhere for %%i in (vswhere.exe) do set "vswhere=%%~$PATH:i"

if defined vswhere for /f "usebackq tokens=*" %%i in (`"%vswhere%" -latest -products * -requires Microsoft.Component.MSBuild -property installationPath`) do set "VSINSTALLDIR=%%i"

if not "%VSINSTALLDIR%" == "" goto AddMsbuildToPath

call :TryVsInstall "%ProgramFiles%\Microsoft Visual Studio\2026\Enterprise"
call :TryVsInstall "%ProgramFiles%\Microsoft Visual Studio\2026\Professional"
call :TryVsInstall "%ProgramFiles%\Microsoft Visual Studio\2026\Community"
call :TryVsInstall "%ProgramFiles%\Microsoft Visual Studio\2026\BuildTools"
call :TryVsInstall "%ProgramFiles%\Microsoft Visual Studio\2022\Enterprise"
call :TryVsInstall "%ProgramFiles%\Microsoft Visual Studio\2022\Professional"
call :TryVsInstall "%ProgramFiles%\Microsoft Visual Studio\2022\Community"
call :TryVsInstall "%ProgramFiles%\Microsoft Visual Studio\2022\BuildTools"

:AddMsbuildToPath
if not "%VSINSTALLDIR%" == "" if exist "%VSINSTALLDIR%\MSBuild\Current\Bin\amd64\MSBuild.exe" set "PATH=%VSINSTALLDIR%\MSBuild\Current\Bin\amd64;%PATH%"
if not "%VSINSTALLDIR%" == "" if exist "%VSINSTALLDIR%\MSBuild\Current\Bin\MSBuild.exe" set "PATH=%VSINSTALLDIR%\MSBuild\Current\Bin;%PATH%"

where msbuild >nul 2>nul
if errorlevel 1 (
    echo Error: msbuild not found. Install Visual Studio or Build Tools.
    exit /b 1
)

echo Building on Windows with MSBuild...
exit /b 0

:TryVsInstall
if "%VSINSTALLDIR%" == "" if exist "%~1\MSBuild\Current\Bin\MSBuild.exe" set "VSINSTALLDIR=%~1"
if "%VSINSTALLDIR%" == "" if exist "%~1\MSBuild\Current\Bin\amd64\MSBuild.exe" set "VSINSTALLDIR=%~1"
exit /b 0
