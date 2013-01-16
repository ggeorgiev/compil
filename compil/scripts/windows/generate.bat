SET GENERATOR=%1

if "%GENERATOR%" == "" (
    SET GENERATOR=..\compil-stable\tool\windowsx86\bin\generator
)

SET BASEDIR=%~dp0
pushd %BASEDIR%\..\..\src || exit 1

%GENERATOR% ^
    --project-file=language\language.scompilprj ^
    --output-directory=language\.gen ^
    --core-output-directory=. ^
    --cpp.include_path=include_path_based_on_package ^
    || exit 1

popd || exit 1