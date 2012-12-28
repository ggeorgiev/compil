#!/bin/bash
BASEDIR=$(dirname $0)
echo $BASEDIR

pushd $BASEDIR || exit 1

chmod 755 tool/macosxx86/bin/generator || exit 1
curl http://localhost:8080/job/compil-deploy-macosx/ADDRESSMODEL=64,ARCHITECTURE=x86,LINK=static,OPERATION_SYSTEM=macosx,TOOLSET=darwin,VARIANT=release/lastSuccessfulBuild/artifact/intermediate/generator/darwin-4.2.1/release/address-model-64/architecture-x86/link-static/threading-multi/generator > tool/macosxx86/bin/generator || exit 1
chmod 755 tool/macosxx86/bin/generator || exit 1

chmod 644 tool/windowsx86/bin/generator.exe || exit 1
curl http://localhost:8080/job/compil-deploy-windows/A=x86,AM=64,L=static,OS=windows,T=msvc-10.0,V=release/lastSuccessfulBuild/artifact/intermediate/generator/672bee5f36160e5defbaeb652e109dfa/generator.exe > tool/windowsx86/bin/generator.exe || exit 1