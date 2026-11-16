@echo off
@REM  Remove the build directory if it exists
if exist ".\build" (
    rmdir ".\build" /s /q
)

set BUILD_CONFIG=Debug

cmake -G "Visual Studio 18 2026" -A x64 -S . -B .\build
cmake --build .\build --config %BUILD_CONFIG%

if exist ".\build\%BUILD_CONFIG%\mpl.exe" (
    .\build\%BUILD_CONFIG%\mpl.exe
) else (
    echo "Executable not found."
)
