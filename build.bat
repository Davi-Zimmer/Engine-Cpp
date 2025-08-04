
REM g++ -static-libstdc++ -static-libgcc -static main.cpp ...

if not exist build (
    mkdir build
)


set filePaths=project/main.cpp project/Window.cpp project/Engine.cpp project/Interpreter.cpp
set gamePaths=project/game/Objects/Rect.cpp

g++ -std=c++17 -pthread %filePaths% %gamePath% module/src/*.c -Imodule/include -Lmodule/lib -lglfw3dll -lopengl32 -lgdi32 -luser32 -o build/app.exe
pause

start build/app.exe
pause