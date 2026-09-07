@echo off
C:\mingw32\bin\windres.exe resource.rc -O coff -o resource.res
C:\mingw32\bin\g++.exe Killer.cpp resource.res -o ChromaWrecker.exe -mwindows -lgdi32 -lmsimg32 -lwinmm -static -static-libgcc -static-libstdc++
pause
