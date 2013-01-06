#!/bin/bash
BASEDIR=$(dirname $0)

pushd $BASEDIR/../../src || exit 1

../compil-stable/tool/linuxx86/bin/generator \
    --project-file=language/language.scompilprj \
    --output-directory=language/.gen \
    --core-output-directory=. \
    --cpp.include_path=include_path_based_on_package \
    || exit 1

popd || exit 1