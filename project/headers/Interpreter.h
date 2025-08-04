#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include "Engine.h"

class Interpreter {
    public:
        Engine engine;
        GLFWwindow* winGL;

        void start();

        Interpreter( Engine e,  GLFWwindow* wGl );


    private:

        void getFps();
        void setFps( std::string stringFps );
        void resizeWin ( std::vector< std::string > );
};