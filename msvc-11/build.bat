@echo off

cd /d %~dp0

pushd .
call ..\compil\scripts\windows\generate.bat || exit 1
popd

call b2 %* || exit 1

@goto :eof

