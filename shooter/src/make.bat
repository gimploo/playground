@echo off

if "%1%"==clean goto CLEAN  

set LIBS=C:\libsdl\lib\x64
set DEPENEDENCIES=SDL2main.lib SDL2.lib shell32.lib

set cwd=%cd%
set FILES=main.c init.c draw.c input.c
set FLAGS=/FC /EHsc /std:c11

echo [*] Compiling ...
mkdir ..\build
pushd ..\build

cl %FLAGS% "%FILE%" /link /LIBPATH:%LIBS% %DEPENEDENCIES% /SUBSYSTEM:WINDOWS /out:shooter.exe

popd

REM call ..\build\%EXE_NAME%.exe
goto EXIT

:CLEAN
echo [*] Cleaning ...
del /Q ..\build\*
rmdir ..\build

:EXIT
echo [!] DONE! 
