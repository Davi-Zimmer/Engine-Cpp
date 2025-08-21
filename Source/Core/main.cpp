#include <glad/glad.h>
#include <GLFW/glfw3.h>
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
#include "../../Includes/Audio/Audio.h"


int main() {

    Audio audio( Utils::pathIn("\\audio.wav").c_str() );
   
    Game* game = Game::GetInstance();

    Engine engine( game );

    Window window( &engine );

    GLFWwindow* winGL = window.createWindow( 600, 400, "Janela" );

    if( !winGL ) return 0;

    Interpreter interpreter( &engine, winGL, &engine.ctx );
    
    EventManager* eventManager = EventManager::GetInstance();

    eventManager->addEvents( winGL );
    
    std::thread interpretadorThread([&interpreter]() {
        interpreter.start();
    });

    window.startLoop();

    if (interpretadorThread.joinable())
        interpretadorThread.join();

    return 0;

}
/*
    fazer a aplicação da matriz de rotação direto na imagem e não quando for desenhar

*/