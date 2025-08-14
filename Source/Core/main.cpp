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


#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

void playDisatster(){
    std::string path = Utils::pathIn( "\\audio.wav" );
        
    PlaySound( path.c_str(), NULL, SND_FILENAME | SND_ASYNC);
    Sleep(3000); // Espera 3 segundos para o som tocar
}


int main() {

    // playDisatster();
   

    Engine engine;

    Window window( engine );

    GLFWwindow* winGL = window.createWindow( 600, 400, "Janela" );

    if( !winGL ) return 0;

    Interpreter interpreter( engine, winGL, engine.ctx );
    
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