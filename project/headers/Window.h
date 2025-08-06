#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Engine.h"

class Window {
    public:
    

        Engine engine;

        GLFWwindow* window;

        Window( Engine eng );

        GLFWwindow* createWindow( int width, int height, const char* windowName );
        
        // void loop( std::function<void()> callback );
        void startLoop();
        void onResize(GLFWwindow* window, int width, int height);
};