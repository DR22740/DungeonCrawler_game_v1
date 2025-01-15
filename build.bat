@echo off
echo Cleaning up old builds...
del *.o
del main.exe

:: Paths
set srcdir=src\
set objdir=src\
set SDLinclude=-ID:\CPPGame\SDL2\include\SDL2 -ID:\CPPGame\SDL2_ttf\x86_64-w64-mingw32\include\SDL2 -I%srcdir%
set SDLlib=-LD:\CPPGame\SDL2\lib -LD:\CPPGame\SDL2_ttf\x86_64-w64-mingw32\lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf

:: Compile Entity.cpp
g++ -std=c++17 -c %srcdir%Entity.cpp -o %objdir%Entity.o %SDLinclude%
if %errorlevel% neq 0 (
    echo Error compiling Entity.cpp
    exit /b 1
)

:: Compile main.cpp
g++ -std=c++17 -c %srcdir%main.cpp -o %objdir%main.o %SDLinclude%
if %errorlevel% neq 0 (
    echo Error compiling main.cpp
    exit /b 1
)

:: Link the program
g++ %objdir%Entity.o %objdir%main.o -o main.exe %SDLlib%
if %errorlevel% neq 0 (
    echo Error linking the program
    exit /b 1
)

echo Build complete! Running the program...
main.exe





















@REM @echo off
@REM echo Cleaning up old builds...
@REM del src\*.o
@REM del main.exe

@REM :: Paths
@REM set srcdir=src\
@REM set objdir=src\
@REM set SDLinclude=-ID:\CPPGame\SDL2\include\SDL2
@REM set SDLlib=-LD:\CPPGame\SDL2\lib -lmingw32 -lSDL2main -lSDL2

@REM @REM :: Compile entity.cpp
@REM @REM echo Compiling entity.cpp...
@REM @REM g++ -std=c++17 -c %srcdir%entity.cpp -o %objdir%entity.o %SDLinclude%
@REM @REM if %errorlevel% neq 0 (
@REM @REM     echo Error compiling entity.cpp
@REM @REM     exit /b 1
@REM @REM )

@REM :: Compile main.cpp
@REM echo Compiling main.cpp...
@REM g++ -std=c++17 -c %srcdir%main.cpp -o %objdir%main.o %SDLinclude%
@REM if %errorlevel% neq 0 (
@REM     echo Error compiling main.cpp
@REM     exit /b 1
@REM )

@REM :: Link and create executable
@REM echo Linking the program...
@REM g++ %objdir%main.o -o main.exe %SDLlib%
@REM if %errorlevel% neq 0 (
@REM     echo Error linking the program
@REM     exit /b 1
@REM )

@REM echo Build complete! Running the program...
@REM main.exe

@REM :: pause for debugging purposes
@REM pause



@REM g++ -std=c++17 -ID:\CPPGame\SDL2\include\SDL2 -c src\main.cpp -o main.o
@REM g++ -std=c++17 -ID:\CPPGame\SDL2\include\SDL2 -c src\entity.cpp -o entity.o

@REM echo Linking the program...
@REM g++ main.o entity.o -o game.exe -LD:\CPPGame\SDL2\lib -lmingw32 -lSDL2main -lSDL2

@REM echo Compilation complete!


@REM :: Build libraries

@REM :: Paths
@REM set srcdir=../src/src/
@REM set objdir=../src/obj/
@REM set SDLinclude=-I ../SDL2/include -L ../SDL2/lib -l SDL2 -l SDL2main



@REM :: Not mine

@REM :: lodepng
@REM g++ -Ofast -c ../src/lodepng/lodepng.cpp ^
@REM     -o %objdir%lodepng.o



@REM :: Mine

@REM :: Utility
@REM g++ -Ofast -c %srcdir%Utility.cpp ^
@REM     -o %objdir%Utility.o

@REM :: Math
@REM g++ -Ofast -c %srcdir%Math.cpp ^
@REM     -o %objdir%Math.o

@REM :: Log
@REM g++ -Ofast -c %srcdir%Log.cpp ^
@REM     -o %objdir%Log.o

@REM :: Vec
@REM g++ -Ofast -c %srcdir%Vec.cpp ^
@REM     -o %objdir%Vec.o

@REM :: Tri
@REM g++ -Ofast -c %srcdir%Tri.cpp ^
@REM     -o %objdir%Tri.o

@REM :: Mesh
@REM g++ -Ofast -c %srcdir%Mesh.cpp ^
@REM     -o %objdir%Mesh.o

@REM :: Camera
@REM g++ -Ofast -c %srcdir%Camera.cpp ^
@REM     -o %objdir%Camera.o

@REM :: Gui
@REM g++ -Ofast -c %srcdir%Gui.cpp ^
@REM     -o %objdir%Gui.o

@REM :: Drawer
@REM g++ -Ofast -c %srcdir%Drawer.cpp ^
@REM     -o %objdir%Drawer.o

@REM :: State
@REM g++ -Ofast -c %srcdir%State.cpp ^
@REM     -o %objdir%State.o

@REM :: ObjectSet
@REM g++ -Ofast -c %srcdir%ObjectSet.cpp ^
@REM     -o %objdir%ObjectSet.o

@REM :: UI
@REM g++ -Ofast -c %srcdir%UI.cpp ^
@REM     -o %objdir%UI.o


@REM :: Build main.exe

@REM :: Compile main.exe
@REM g++ -Ofast ../main.cpp ^
@REM     %objdir%Utility.o ^
@REM     %objdir%Math.o ^
@REM     %objdir%Log.o ^
@REM     %objdir%Vec.o ^
@REM     %objdir%Tri.o ^
@REM     %objdir%Camera.o ^
@REM     %objdir%Mesh.o ^
@REM     %objdir%Gui.o ^
@REM     %objdir%Drawer.o ^
@REM     %objdir%State.o ^
@REM     %objdir%ObjectSet.o ^
@REM     %objdir%UI.o ^
@REM     %objdir%lodepng.o ^
@REM     -o main.exe ^
@REM     -mwindows

@REM main.exe

@REM :: pause for debugging purposes
@REM pause
