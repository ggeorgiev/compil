@echo off

cd /d %~dp0

call build.bat %1 %2 src %4 || exit 1

pushd .
call ..\compil\scripts\windows\generate-tests.bat || exit 1
popd

call b2 %* || exit 1

@goto :eof

