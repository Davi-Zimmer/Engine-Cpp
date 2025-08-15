#include <iostream>
#include <thread>
#include "../../Includes/Core/Engine.h"
#include "../../Includes/Graphics/Canvas2D.h"
#include "../../Includes/Managers/EventManager.h"

#include <SFML/System.hpp>

bool countFps = true;

Engine::Engine(){

    setFpsTarget( 60 );
    
    timePerFrame = .0f / targetFps;
    
    fpsCounter =.0f;
    framesRendered = 0;

    ctx = Canvas2D();
    
}

int Engine::setFpsTarget( int fps )
{
    targetFps = fps;
    return targetFps;
}

int Engine::getFpsTarget()
{
    return targetFps;
}


void Engine::frameSkipper(GLFWwindow* window){
    ctx.renderConstructor();

    const float targetFrameTime = 1.0f / targetFps;
    sf::Clock clock;
    float fpsTimer = 0.0f;
    int frameCount = 0;


    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        float deltaTime = clock.restart().asSeconds();
        
        EventManager::GetInstance()->processHoldKeys();

        render( window, deltaTime );

        fpsTimer += deltaTime;
        frameCount++;
        if (fpsTimer >= 1.0f) {
            //std::cout << "FPS: " << frameCount << std::endl;
            FPS = frameCount;
            fpsTimer -= 1.0f;
            frameCount = 0;
        }

        float sleepSeconds = targetFrameTime - clock.getElapsedTime().asSeconds();
        if (sleepSeconds > 0){

            sf::sleep(sf::seconds(sleepSeconds));

        }

    }

}

int Engine::getFps_(){ 
    std::cout << "[DEBUG] setFps_: " << FPS << std::endl;
    return FPS; }
void Engine::setFps_( int fps ){ FPS = fps; }

void Engine::render( GLFWwindow* window, double deltaTime ){
    ctx.renderConfigs( window, deltaTime );
}

void Engine::windowResized( GLFWwindow* window, int width, int height ){
    ctx.setCanvasSize( width, height );
    
}