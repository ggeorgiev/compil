cd /d %~dp0

SET GENERATOR=%1

if "%GENERATOR%" == "" (
    SET GENERATOR=..\..\intermediate\dist\generator.exe
)

echo TESTS-GENERATOR=%GENERATOR%

SET BASEDIR=%~dp0
pushd %BASEDIR%\..\..\src || exit 1

%GENERATOR% ^
    --double-buffer-directory=..\..\intermediate\double_buffer ^
    --project-file=generator-test\generator-test.compilprj ^
    --output-directory=generator-test\.gen ^
    --core-output-directory=. ^
    --cpp.include_path=include_path_based_on_package ^
    || exit 1

popd || exit 1

