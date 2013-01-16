#!/bin/bash

BASEDIR=$(dirname $0)
$BASEDIR/generate.sh || exit 1

## generate valgrind config file
echo '--memcheck:track-origins=yes' > .valgrindrc
echo '--memcheck:leak-check=full' >> .valgrindrc
echo '--memcheck:show-reachable=yes' >> .valgrindrc
echo '--memcheck:xml=yes' >> .valgrindrc
echo '--memcheck:xml-file=compil_valgrind.%p.xml' >> .valgrindrc

# generate Valgrind report
../boost/tool/linuxx86/bin/b2 \
    -s USE_VALGRIND=true \
    debug-symbols=on \
    toolset=gcc \
    variant=debug \
    architecture=x86 \
    address-model=64 \
    link=static \
    runtime-link=shared \
    || exit 1
    
../boost/tool/linuxx86/bin/b2 \
    -s USE_VALGRIND=true \
    debug-symbols=on \
    toolset=gcc \
    variant=release \
    architecture=x86 \
    address-model=64 \
    link=static \
    runtime-link=shared \
    || exit 1