#!/bin/bash
BASEDIR=$(dirname $0)
$BASEDIR/generate.sh || exit 1

../boost/tool/linuxx86/bin/b2 \
    cxxflags=--coverage \
    linkflags=--coverage \
    toolset=gcc \
    variant=release \
    debug-symbols=on \
    architecture=x86 \
    address-model=64 \
    link=static \
    runtime-link=shared \
    || exit 1

# generate cobertura reports
../scripts/linux/gcovr \
    --verbose \
    --root . \
    --object-directory ../../intermediate/* \
    --output coverage-gen.xml \
    --xml \
    || exit 1


