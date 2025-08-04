#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Engine.h"

class Window {
    public:
    
        static void FramebufferCallback(GLFWwindow* window, int width, int height);

        GLFWwindow* window;

        Window();

        GLFWwindow* createWindow( int width, int height, const char* windowName );
        
        // void loop( std::function<void()> callback );
        void startLoop( Engine engine );

};