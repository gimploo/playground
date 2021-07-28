@echo off

:: NOTE: 
::      Have added the headerfiles to two places i.e 
:: @wsl2 /usr/include/SDL2 and 
:: @um/ with all the other cl header files 
:: this would allow the intellisense to work in both vscode and vim(wsl)
::      Couldnt find a way to have the libraries work with cl compiler without
:: having to include it manually 
:: 
:: NOTE: DONT USE SDL WITH GCC its windows specific 
::
:: SOURCE -> https://stackoverflow.com/questions/30178703/compile-a-c-sdl-program-with-visual-c-2013-from-the-command-line

:: Better build 
cl test.c /link /LIBPATH:C:\3rd_party_C_libraries\SDL2-2.0.14\lib\x64 SDL2main.lib SDL2.lib shell32.lib /SUBSYSTEM:WINDOWS

:: Works (including the headerfilees and libraries manually)
REM cl /FC test.c /I .\include /link lib\x64\SDL2main.lib lib\x64\SDL2.lib shell32.lib /SUBSYSTEM:CONSOLE

:: DOESNT work
 REM cl test.c SDL2main.lib SDL2.lib shell32.lib /SUBSYSTEM:CONSOLE

:: WORKS (only including libraries manually)
REM cl /FC test.c /link lib\x64\SDL2main.lib lib\x64\SDL2.lib shell32.lib /SUBSYSTEM:WINDOWS


