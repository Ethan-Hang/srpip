@echo off

set SYSCFG_PATH="C:\ti\sysconfig_1.21.0\sysconfig_cli.bat"
set SDK_ROOT="C:\ti\mspm0_sdk_2_05_01_00"

if not exist %SYSCFG_PATH% (
    echo.
    echo Couldn't find Sysconfig Tool %SYSCFG_PATH%
    echo.
    exit /b 1
)

echo Using Sysconfig Tool from %SYSCFG_PATH%

set PROJ_DIR=%~1
set PROJ_DIR=%PROJ_DIR:'=%

set SYSCFG_FILE=%~2
set SYSCFG_FILE=%SYSCFG_FILE:'=%

:: Set SYSCFG_DIR to parent directory of project (project root)
set SYSCFG_DIR=%PROJ_DIR%..
IF %SYSCFG_DIR:~-1%==\ SET SYSCFG_DIR=%SYSCFG_DIR:~0,-1%

:: Construct full path to syscfg file
set FULL_SYSCFG_PATH=%PROJ_DIR%%SYSCFG_FILE%

%SYSCFG_PATH% -o "%SYSCFG_DIR%" -s "%SDK_ROOT%\.metadata\product.json" --compiler keil "%FULL_SYSCFG_PATH%"
