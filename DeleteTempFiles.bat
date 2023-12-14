@echo off
echo.
echo Cleaning your project. Please wait...
echo.

@REM Delete temporary project files
for /d %%d in (".vs", "Binaries", "Build", "Intermediate", "Saved", "DerivedDataCache", "Content\DownloadCache") do (
    @IF EXIST "%%d" rd /s /q %%d
)
if exist "Glowstick.sln" del /q "Glowstick.sln"

@REM Check if Unreal tasks are running
@REM tasklist | findstr /i /r "UnrealEditor.exe" > nul
@REM set taskFound=0
@REM for /f %%i in ('tasklist ^| findstr /i /r "UnrealEditor.exe"') do (
@REM     set taskFound=1
@REM     echo File locked by %%i
@REM )

@REM if errorlevel 1 (

    set allDeleted=1
    echo.

    @REM Check for any remaining temporary files
    for /d %%d in (".vs", "Binaries", "Build", "Intermediate", "Saved", "DerivedDataCache", "Content\DownloadCache") do (
        IF EXIST "%%d" (
            color 4
            echo Error: %%d was not deleted. Delete it before proceeding.
            set allDeleted=0
        )
    )

    if %allDeleted%==1 (
            color
            echo Your project has been cleaned.
    )
@REM ) else (
    @REM Print error message
    @REM color 4
    @REM echo.
    @REM echo ************************************************************************************************
    @REM echo Cannot clean up project while an Unreal process is running. Please close the engine and try again.
    @REM echo ************************************************************************************************
@REM )

echo.
pause