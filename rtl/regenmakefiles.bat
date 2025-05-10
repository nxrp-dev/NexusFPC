@echo off

SETLOCAL EnableDelayedExpansion

REM Check directory

IF "%~1" NEQ "" (
	SET RTLDIR=%~1
) ELSE (
	SET RTLDIR=%CD%
)

REM Check RTL dir?

IF NOT EXIST "%RTLDIR%\ucmaps" (
	ECHO This script must be executed in the rtl directory or have an argument to specify the RTL directory
	ENDLOCAL
	EXIT 1
)

REM fpcmake to use

IF EXIST "%RTLDIR%\..\utils\fpcm\fpcmake.exe" (
	SET FPCMAKE="%RTLDIR%\..\utils\fpcm\fpcmake.exe"
) ELSE (
	SET FPCMAKE=fpcmake.exe
)

REM Go

ECHO Using fpcmake: "%FPCMAKE%"

REM Main

echo Doing RTL toplevel dir: "%RTLDIR%"

pushd "%RTLDIR%"
%FPCMAKE% -q -Tall
popd

REM OS-specific

GOTO :Generate

:GenerateMakefile
	SET d=%~1
	SET TARGETS=%~2
	IF EXIST "!d!\Makefile.fpc" (
		ECHO Doing directory %d%
		PUSHD "!d!"
		SET CMD=%FPCMAKE% -T!TARGETS! -q -x "%RTLDIR%\inc\Makefile.rtl"
		echo Command: !CMD!
		!CMD!
		POPD
	)
GOTO :EOF

:Generate
FOR /D %%d IN ("%RTLDIR%\*") DO (
	IF "%%~nd" EQU "darwin" (
		SET TARGETS=darwin,ios,iphonesim
	) ELSE IF "%%~nd" EQU "macos" (
		SET TARGETS=macosclassic
	) ELSE (
		SET TARGETS=%%~nd
	)
 	CALL :GenerateMakefile %RTLDIR%\%%~nd , "!TARGETS!"
)

CALL :GenerateMakefile "%RTLDIR%\android\jvm" , "jvm-android"

REM That's all, folks!

ENDLOCAL
