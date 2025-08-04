#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>
#include <thread>
#include "./headers/Window.h"
#include "./headers/Engine.h"

Window::Window(){

    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW.\n";
        return;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

}

void Window::FramebufferCallback(GLFWwindow* window, int width, int height )
{
    glViewport(0, 0, width, height);
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

    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback( window, FramebufferCallback );

    return window;
}

void Window::startLoop( Engine engine ){
    
    engine.frameSkipper( window );
    
    glfwTerminate();

}
