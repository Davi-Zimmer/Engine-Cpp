#include <iostream>
#include <thread>
#include "./headers/Engine.h"
#include "headers/Canvas2D.h"


Engine::Engine(){

    setFpsTarget( 30 );
    
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

void Engine::frameSkipper( GLFWwindow* window )
{

    auto  lastTime = std::chrono::high_resolution_clock::now();
    auto  fpsTimer = std::chrono::high_resolution_clock::now();
    float accumulator = .0f;
    
    ctx.renderConstructor();

    while(!glfwWindowShouldClose(window))
    {
        // Medir tempo desde o último loop
        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> delta = currentTime - lastTime;
        lastTime = currentTime;

        accumulator += delta.count();
        fpsCounter += delta.count();

        // FPS real
        if (fpsCounter >= 1.0f) {
            // std::cout << "FPS: " << framesRendered << std::endl;
            fpsCounter = 0.0f;
            framesRendered = 0;
        }

        // Se passou tempo suficiente, renderiza um frame
        if (accumulator >= timePerFrame) {
            accumulator -= timePerFrame;
            framesRendered++;
        }
        
        render( window );

    }

}

void Engine::render( GLFWwindow* window ){
    glClear(GL_COLOR_BUFFER_BIT);

    ctx.render();

    glfwSwapBuffers(window);
    glfwPollEvents();
}