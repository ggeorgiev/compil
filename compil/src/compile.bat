..\compil-stable\tool\windowsx86\bin\generator --project-file=language\language.scompilprj -o language\.gen || exit 1
..\boost\tool\windowsx86\bin\b2.exe toolset=msvc-10.0 variant=debug address-model=32 architecture=x86 link=static runtime-link=static -j8