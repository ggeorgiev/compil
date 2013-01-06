#!/bin/bash

## generate valgrind config file
echo '--memcheck:track-origins=yes' > .valgrindrc
echo '--memcheck:leak-check=full' >> .valgrindrc
echo '--memcheck:show-reachable=yes' >> .valgrindrc
echo '--memcheck:xml=yes' >> .valgrindrc
echo '--memcheck:xml-file=compil_valgrind.%p.xml' >> .valgrindrc

# generate Valgrind report
../compil-stable/tool/linuxx86/bin/generator --project-file=language/language.scompilprj -o language/.gen --core-output-directory=. --cpp.include_path=include_path_based_on_package || exit 1
../boost/tool/linuxx86/bin/b2 -s USE_VALGRIND=true toolset=gcc variant=release,debug architecture=x86 address-model=64 link=static runtime-link=shared || exit 1