#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../../Includes/Core/Window.h"
#include "../../Includes/Core/Engine.h"
#include "../../Includes/Utils/Interpreter.h"

#include "../../Includes/Graphics/Canvas2D.h"
#include <iostream>
#include <thread>
#include <string>
#include <atomic>

#include <vector>
#include <sstream>

#include <iostream>
#include <AL/al.h>
#include <AL/alc.h>
#include "../../Includes/Audio/Audio.h"
#include "../../Includes/Utils/Utils.h"
#include "../../includes/Managers/EventManager.h"

#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

void playDisatster(){
    std::string path = Utils::pathIn( "\\audio.wav" );
        
    PlaySound( path.c_str(), NULL, SND_FILENAME | SND_ASYNC);
    Sleep(3000); // Espera 3 segundos para o som tocar
}


void callback( GLFWwindow *window, int key, int scancode, int action, int mods ){

}

int main() {

    // playDisatster();
   
    Engine engine;

    Window window( &engine );

    GLFWwindow* winGL = window.createWindow( 600, 400, "Janela" );

    if( !winGL ) return 0;

    Interpreter interpreter( &engine, winGL, &engine.ctx );
    
    EventManager* eventManager = EventManager::GetInstance();

    glfwSetWindowUserPointer(winGL, eventManager);


    glfwSetKeyCallback(winGL, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        auto* em = static_cast<EventManager*>(glfwGetWindowUserPointer(window));
        em->keyCallback(window, key, scancode, action, mods);
    });
    
    glfwSetMouseButtonCallback(winGL, [](GLFWwindow* window, int button, int action, int mods) {
        auto* em = static_cast<EventManager*>(glfwGetWindowUserPointer(window));
        em->mouseButtonsCallback( window, button, action, mods );
    });
        
    glfwSetCursorPosCallback(winGL, [](GLFWwindow* window, double xpos, double ypos) {
        auto* em = static_cast<EventManager*>(glfwGetWindowUserPointer(window));
        em->mouseMoveCallback(xpos, ypos);  // você implementa dentro do EventManager
    });

    glfwSetScrollCallback(winGL, [](GLFWwindow* window, double xoffset, double yoffset) {
        auto* em = static_cast<EventManager*>(glfwGetWindowUserPointer(window));
        em->scrollCallback(xoffset, yoffset);
    });


    std::thread interpretadorThread([&interpreter]() {
        interpreter.start();
    });

    window.startLoop();

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