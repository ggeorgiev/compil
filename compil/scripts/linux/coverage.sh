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
    --root ../../intermediate/generator-test/gcc-4.7/release/address-model-64/architecture-x86/debug-symbols-on/link-static/threading-multi \
    --object-directory ../../intermediate/* \
    --output coverage-gen.xml \
    --xml \
    || exit 1
    
../scripts/linux/gcovr \
    --root ../../intermediate \
    --object-directory ../../intermediate/* \
    --exclude /debug-symbols-on/ \
    --output coverage-app.xml \
    --xml \
    || exit 1

../scripts/linux/gcovr \
    --root ../../intermediate/compil/src \
    --object-directory ../../intermediate/* \
    --output coverage-src.xml \
    --xml \
    || exit 1

