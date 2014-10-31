@echo off

rem Remove all CMake directories.
for /d %%x in ("CMake-*") do rd /s /q "%%x"
