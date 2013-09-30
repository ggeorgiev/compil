cd /d %~dp0

@echo on

pushd .
call ..\compil\scripts\windows\generate.bat || exit 1
popd

SET VARIANT=%1
SET ADDRESS_MODEL=%2
SET SUBDIR=%3
SET TARGET=%4

SET BUILD=%cd%\..\compil\boost\tool\windowsx86\bin\b2

echo on
pushd ..\compil\%SUBDIR% || exit 1
echo %cd%
%BUILD% --hash ^
        toolset=msvc-10.0 link=static runtime-link=static architecture=x86 threading=multi ^
        variant=%VARIANT% address-model=%ADDRESS_MODEL% -j%NUMBER_OF_PROCESSORS% ^
        -sPERFORMANCE_TEST_REPEAT=%PERFORMANCE_TEST_REPEAT% ^
        debug-symbols=on ^
        %TARGET%
@popd || exit 1
@goto :eof

