#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include "../Graphics/Canvas2D.h"
#include "../Core/Engine.h"

class Interpreter {
    public:
        Engine* engine;
        GLFWwindow* winGL;
        Canvas2D* ctx;
        void start();

        Interpreter( Engine* e,  GLFWwindow* wGl, Canvas2D* canvas );


    private:

        void getFps();
        void setFps( std::string stringFps );
        void resizeWin ( std::vector< std::string > );
        void moveObj( std::vector< std::string > args );
        void resizeeObj( std::vector< std::string > args );
        void getFpsLixo();

    };