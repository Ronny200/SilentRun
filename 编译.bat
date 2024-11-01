@echo off
rem cd MinGW\bin
rem windres.exe ..\..\run.rc -o ..\..\run.res.o
rem cd ..\..\
rem tcc -c run.c -o run.o
tcc -o tool.exe run.o run.res.o
rem tcc -o tool.exe run.o run.res.o -Wl,--subsystem,windows
start "" "D:\Green\Tcc\tcc.exe" -o SilentRun.exe SilentRun.c -Wl,--subsystem,windows
