call ..\scripts\windows\generate.bat || exit 1
..\boost\tool\windowsx86\bin\b2.exe toolset=msvc-10.0 variant=release address-model=64 architecture=x86 link=static runtime-link=static -j8