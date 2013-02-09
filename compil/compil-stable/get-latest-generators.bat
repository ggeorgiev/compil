SET BASEDIR=%~dp0
echo %BASEDIR%

SET HOST=192.168.1.76

pushd %BASEDIR% || exit 1

curl -o tool\macosxx86\bin\generator "http://%HOST%:8080/view/compil/job/compil-deploy-macosx/lastSuccessfulBuild/artifact/intermediate/generator/darwin-4.2.1/release/address-model-64/architecture-x86/link-static/threading-multi/generator" || exit 1
curl -o tool\linuxx86\bin\generator "http://%HOST%:8080/view/compil/job/compil-deploy-linux/lastSuccessfulBuild/artifact/intermediate/generator/gcc-4.7/release/address-model-64/architecture-x86/link-static/threading-multi/generator" || exit 1
curl -o tool\windowsx86\bin\generator.exe "http://%HOST%:8080/view/compil/job/compil-deploy-windows/lastSuccessfulBuild/artifact/intermediate/generator/672bee5f36160e5defbaeb652e109dfa/generator.exe" || exit 1

popd || exit 1