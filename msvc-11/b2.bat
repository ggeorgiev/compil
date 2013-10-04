cd /d %~dp0

@echo on

SET VARIANT=%1
SET ADDRESS_MODEL=%2
SET SUBDIR=%3
SET TARGET=%4

SET BUILD=%cd%\..\compil\boost\tool\windowsx86\bin\b2

echo on
pushd ..\compil\%SUBDIR% || exit 1
echo %cd%

::set COVERITY=cov-build --dir ..\..\intermediate\cov-int

%COVERITY% ^
%BUILD% --hash ^
        toolset=msvc-11.0 link=static runtime-link=static architecture=x86 threading=multi ^
        variant=%VARIANT% address-model=%ADDRESS_MODEL% -j%NUMBER_OF_PROCESSORS% ^
        debug-symbols=on ^
        %TARGET%
@popd || exit 1

@goto :eof
