@echo off
cl main.c /link /LIBPATH:C:\libsdl\lib\x64 SDL2main.lib SDL2.lib shell32.lib /SUBSYSTEM:WINDOWS

