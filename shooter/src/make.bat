@echo off

if "%1"=="clean" goto CLEAN  

call cl
if %ERRORLEVEL% NEQ 0 (
    echo [!] Setting up envirnoment ...
    call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
    if %ERRORLEVEL% NEQ 1 (
        echo [!] vcvarsall.bat not found
        goto EXIT
    )
)

set src=%cd%
set MAINFILE=%src%\main.c

REM ENV variables
set INCLUDE=C:\libc\SDL\include;C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Tools\MSVC\14.27.29110\include;C:\Program Files (x86)\Windows Kits\10\include\10.0.18362.0\ucrt;C:\Program Files (x86)\Windows Kits\10\include\10.0.18362.0\shared;C:\Program Files (x86)\Windows Kits\10\include\10.0.18362.0\um;C:\Program Files (x86)\Windows Kits\10\include\10.0.18362.0\winrt;C:\Program Files (x86)\Windows Kits\10\include\10.0.18362.0\cppwinrt;
set LIB=C:\libc\SDL\lib\x64;C:\libc\SDL_image\lib\x64;C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Tools\MSVC\14.27.29110\lib\x64;C:\Program Files (x86)\Windows Kits\10\lib\10.0.18362.0\ucrt\x64;C:\Program Files (x86)\Windows Kits\10\lib\10.0.18362.0\um\x64;

set DEPENDENCIES=SDL2.lib SDL2main.lib SDL2_image.lib shell32.lib
set FILES=%src%\init.c %src%\draw.c %src%\input.c 
set OBJS=init.obj draw.obj input.obj
set FLAGS=/nologo /Zi

set EXE=..\build\shooter.exe

echo [*] Compiling ...
echo [*] Creating Objects ...

mkdir ..\build
pushd ..\build

cl /nologo /c %FILES% /link %DEPENDENCIES% /SUBSYSTEM:WINDOWS
if %ERRORLEVEL% NEQ 0 (
    echo [!] Failed to create object!
    popd
    goto EXIT
)
echo [!] Successfully Created Objects!

echo [*] Linking Objects ...

cl %FLAGS% %MAINFILE% /link %OBJS% %DEPENDENCIES% /SUBSYSTEM:WINDOWS /out:shooter.exe
if %ERRORLEVEL% NEQ 0 (
    echo [!] Failed to link object!
    popd
    goto EXIT
)
echo [!] Successfully Linked Objects!

popd

if "%1"=="run" (
    echo [!] Running executable!
    call %EXE%
)

echo [!] DONE! 

goto EXIT


:CLEAN
echo [*] Cleaning ...
del /Q ..\build\*.obj 
del /Q ..\build\*.exe 
del /Q ..\build\*.ilk 
del /Q ..\build\*.pdb
echo [!] DONE! 

:EXIT

