#pragma once

#include <iostream>
#include <chrono>
#include <thread>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../Graphics/Canvas2D.h"

class Engine {

    public:

        int targetFps;

        float timePerFrame;

        float fpsCounter;
        int framesRendered;

        float FPS = 0;

        Canvas2D ctx;

        std::chrono::_V2::system_clock::time_point lastTime;
        std::chrono::_V2::system_clock::time_point fpsTimer;

        Engine();

        int setFpsTarget( int fps );
        
        int getFpsTarget();

        void frameSkipper( GLFWwindow* window );

        void render( GLFWwindow* window, double deltaTime );
        
        void windowResized( GLFWwindow* window, int width, int height );

        int getFps_();
        void setFps_( int fps ); 
};