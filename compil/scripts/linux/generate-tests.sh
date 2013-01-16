#!/bin/bash
GENERATOR=$1

if [ -z "$GENERATOR" ]
then
    GENERATOR=../compil-stable/tool/linuxx86/bin/generator
fi

echo GENERATOR=$GENERATOR

BASEDIR=$(dirname $0)

pushd $BASEDIR/../../src || exit 1

$GENERATOR \
    --project-file=generator-test/generator-test.compilprj \
    --output-directory=generator-test/.gen \
    --core-output-directory=. \
    --cpp.include_path=include_path_based_on_package \
    || exit 1

popd || exit 1