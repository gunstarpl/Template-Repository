@echo off

rem Cleanup first.
call CMake-Cleanup.bat

rem Create an empty directory.
mkdir "CMake-VS2013"
cd "CMake-VS2013"

rem Generate solution files.
cmake -G "Visual Studio 12" ./..

rem Prevent console from closing.
pause
