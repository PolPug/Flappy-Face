@echo off
REM === Build Raylib Game ===

set COMPILER=C:\raylib\w64devkit\bin\g++.exe
set OUT=game.exe
set INCLUDE=-IC:\raylib\raylib\src
set LIB=-LC:\raylib\raylib\src -lraylib -lopengl32 -lgdi32 -lwinmm

REM List your source files
set SRC=main.cpp Classes/Bird.cpp Classes/Pipe.cpp

REM Step 1: Compile each .cpp into .o
for %%f in (%SRC%) do (
    echo Compiling %%f...
    "%COMPILER%" -c %%f %INCLUDE%
)

REM Step 2: Link all .o files   
echo Linking...
"%COMPILER%" *.o -o %OUT% %LIB% -mwindows

if %errorlevel% neq 0 (
    echo Build failed!
) else (
    echo Build successful! Output: %OUT%
)
del *.o
pause