@echo off
echo Cleaning up old builds...
del *.o
del main.exe

:: Dynamically set paths
set srcdir=%CD%\src
set objdir=%CD%\src
set SDLinclude=-I%CD%\SDL2\include\SDL2 -I%CD%\SDL2_ttf\x86_64-w64-mingw32\include\SDL2 -I%srcdir%
set SDLlib=-L%CD%\SDL2\lib -L%CD%\SDL2_ttf\x86_64-w64-mingw32\lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf

:: Compile Entity.cpp
g++ -std=c++17 -c %srcdir%\Entity.cpp -o %objdir%\Entity.o %SDLinclude%
if %errorlevel% neq 0 (
    echo Error compiling Entity.cpp
    exit /b 1
)

:: Compile Player.cpp
g++ -std=c++17 -c %srcdir%\Player.cpp -o %objdir%\Player.o %SDLinclude%
if %errorlevel% neq 0 (
    echo Error compiling Player.cpp
    exit /b 1
)

:: Compile Mob.cpp
g++ -std=c++17 -c %srcdir%\Mob.cpp -o %objdir%\Mob.o %SDLinclude%
if %errorlevel% neq 0 (
    echo Error compiling Mob.cpp
    exit /b 1
)

:: Compile Wall.cpp
g++ -std=c++17 -c %srcdir%\Wall.cpp -o %objdir%\Wall.o %SDLinclude%
if %errorlevel% neq 0 (
    echo Error compiling Wall.cpp
    exit /b 1
)

:: Compile graphics.cpp
g++ -std=c++17 -c %srcdir%\graphics.cpp -o %objdir%\graphics.o %SDLinclude%
if %errorlevel% neq 0 (
    echo Error compiling graphics.cpp
    exit /b 1
)

:: Compile main.cpp
g++ -std=c++17 -c %srcdir%\main.cpp -o %objdir%\main.o %SDLinclude%
if %errorlevel% neq 0 (
    echo Error compiling main.cpp
    exit /b 1
)

:: Link the program
g++ %objdir%\main.o %objdir%\graphics.o %objdir%\Entity.o %objdir%\Player.o %objdir%\Mob.o %objdir%\Wall.o -o main.exe %SDLlib% %SDLinclude%
if %errorlevel% neq 0 (
    echo Error linking the program
    exit /b 1
)

echo Build complete! Running the program...
main.exe
