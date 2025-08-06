#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>
#include <thread>
#include "./headers/Window.h"
#include "./headers/Engine.h"

void FramebufferCallback(GLFWwindow* window, int width, int height) {
    // Pegamos o ponteiro que você salvou anteriormente
    Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (win) {
        win->onResize(window, width, height);
    }
}

Window::Window( Engine eng ){

    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW.\n";
        return;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    engine = eng;


}


GLFWwindow* Window::createWindow( int width, int height, const char* windowName )
{
    window = glfwCreateWindow( width, height, windowName, NULL, NULL );
    
    if( window == NULL )
    {
        std::cout << "Failed to open GLFW window.\n";
        return NULL;
    }

    glfwMakeContextCurrent( window );

    if (!gladLoadGLLoader( (GLADloadproc)glfwGetProcAddress) )
    {
        std::cout << "Failed to initialize GLAD.\n";
        return NULL;
    }

    engine.windowResized( window, width, height );

    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, FramebufferCallback);


    return window;
}

void Window::startLoop(){
    
    engine.frameSkipper( window );
    
    glfwTerminate();

}

void Window::onResize(GLFWwindow* window, int width, int height)
{
    engine.windowResized( window, width, height);
}
