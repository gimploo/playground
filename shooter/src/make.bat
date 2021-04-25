@echo off

if "%1%"==clean goto CLEAN  

set LIBS=C:\libsdl\lib\x64
set DEPENEDENCIES=SDL2main.lib SDL2.lib shell32.lib

set cwd=%cd%
set MAINFILE=%cwd%\main.c
set HEADERS=init.c draw.c input.c 
set OBJS=%cwd%\init.obj %cwd%\draw.obj %cwd%\input.obj
set FLAGS=/FC /EHsc

set EXE=..\build\shooter.exe

echo [*] Compiling ...
echo [*] Creating Objects ...

cl /C %HEADERS% /link /LIBPATH:%LIBS% %DEPENEDENCIES% /SUBSYSTEM:WINDOWS

echo [*] Linking Objects ...
mkdir ..\build
pushd ..\build

cl %FLAGS% %MAINFILE% %OBJS% /link /LIBPATH:%LIBS% %DEPENEDENCIES% /SUBSYSTEM:WINDOWS /out:shooter.exe

popd

del /Q *.obj

call %EXE%

goto EXIT

:CLEAN
echo [*] Cleaning ...
del /Q ..\build\*

:EXIT
echo [!] DONE! 
