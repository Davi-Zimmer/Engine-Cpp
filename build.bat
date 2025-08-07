
REM g++ -static-libstdc++ -static-libgcc -static main.cpp ...

if not exist build (
    mkdir build
)


set filePaths=project/main.cpp project/Window.cpp project/Engine.cpp project/Interpreter.cpp project/Canvas2D.cpp project/Image.cpp project/Matrix.cpp
set gamePaths=project/game/Objects/Rect.cpp

g++ -std=c++17 -pthread %filePaths% %gamePaths% module/src/*.c -Imodule/include -Lmodule/lib -lglfw3dll -lopengl32 -lgdi32 -luser32 -lstdc++fs -o build/app.exe

start build/app.exe
pause