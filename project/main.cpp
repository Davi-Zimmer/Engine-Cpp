#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "./headers/Window.h"
#include "./headers/Engine.h"
#include "./headers/Interpreter.h"
#include <iostream>
#include <thread>
#include <string>
#include <atomic>

#include <vector>
#include <sstream>




int main() {

    Window window;
    Engine engine;

    GLFWwindow* winGL = window.createWindow( 600, 400, "Janela" );

    if( !winGL ) return 0;

    Interpreter interpreter( engine, winGL );
    
    std::thread interpretadorThread([&interpreter]() {
        interpreter.start();
    });

    window.startLoop( engine );

    if (interpretadorThread.joinable())
        interpretadorThread.join();


    return 0;

}
/*

function splitCommand( stringCommand ){
    const args = stringCommand.split(' ')
    return args
}
*/