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

lcov -o full.info -c --directory ../../intermediate/ || exit 1

if [ ! -d coverage ]
then
    mkdir coverage || exit 1
fi

lcov -e full.info "$PWD/*" -o src.info || exit 1
lcov -r src.info *-gtest* *-partial* -o compil.info || exit 1
genhtml --no-branch-coverage -o ./coverage compil.info || exit 1
rm -rf /var/www/coverage || exit 1
mv coverage /var/www || exit 1
rm *.info || exit 1
