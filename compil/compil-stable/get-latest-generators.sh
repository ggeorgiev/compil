#!/bin/bash
BASEDIR=$(dirname $0)
echo $BASEDIR

pushd $BASEDIR || exit 1

chmod 755 tool/macosxx86/bin/generator || exit 1
curl http://192.168.1.73:8080/view/compil/job/compil-deploy-macosx/lastSuccessfulBuild/artifact/intermediate/generator/darwin-4.2.1/release/address-model-64/architecture-x86/link-static/threading-multi/generator > tool/macosxx86/bin/generator || exit 1
chmod 755 tool/macosxx86/bin/generator || exit 1

chmod 755 tool/linuxx86/bin/generator || exit 1
curl http://192.168.1.73:8080/view/compil/job/compil-deploy-linux/lastSuccessfulBuild/artifact/intermediate/generator/gcc-4.7/release/address-model-64/architecture-x86/link-static/threading-multi/generator > tool/linuxx86/bin/generator || exit 1
chmod 755 tool/linuxx86/bin/generator || exit 1

chmod 644 tool/windowsx86/bin/generator.exe || exit 1
curl http://192.168.1.73:8080/view/compil/job/compil-deploy-windows/lastSuccessfulBuild/artifact/intermediate/generator/672bee5f36160e5defbaeb652e109dfa/generator.exe > tool/windowsx86/bin/generator.exe || exit 1

popd || exit 1