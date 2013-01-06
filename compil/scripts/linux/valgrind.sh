#!/bin/bash

## generate valgrind config file
echo '--memcheck:track-origins=yes' > .valgrindrc
echo '--memcheck:leak-check=full' >> .valgrindrc
echo '--memcheck:show-reachable=yes' >> .valgrindrc
echo '--memcheck:xml=yes' >> .valgrindrc
echo '--memcheck:xml-file=compil_valgrind.%p.xml' >> .valgrindrc

# generate Valgrind report
../boost/tool/linuxx86/bin/b2 -s USE_VALGRIND=true toolset=gcc variant=release,debug architecture=x86 address-model=64 link=static runtime-link=shared