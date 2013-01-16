SET GENERATOR=%1

if "%GENERATOR%" == "" (
    SET GENERATOR=..\compil-stable\tool\windowsx86\bin\generator
)

echo GENERATOR=%GENERATOR%

%GENERATOR% ^
    --project-file=generator-test\generator-test.compilprj ^
    --output-directory=generator-test\.gen ^
    --core-output-directory=. ^
    --cpp.include_path=include_path_based_on_package ^
    || exit 1

popd || exit 1
