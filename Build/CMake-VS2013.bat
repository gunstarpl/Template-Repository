@echo off

rem Cleanup first.
call CMake-Cleanup.bat

rem Create an empty output directory.
mkdir Output
cd Output

rem Generate solution files.
cmake -g "Visual Studio 12" ./..

rem Prevent console from closing.
pause
