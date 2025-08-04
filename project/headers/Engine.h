#pragma once

#include <iostream>
#include <chrono>
#include <thread>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Engine {

    public:

        int targetFps;

        float timePerFrame;

        float fpsCounter;
        int framesRendered;

        
        std::chrono::_V2::system_clock::time_point lastTime;
        std::chrono::_V2::system_clock::time_point fpsTimer;

        Engine();

        int setFpsTarget( int fps );
        
        int getFpsTarget();

        void frameSkipper( GLFWwindow* window );

        void renderConstructor();

        void render( GLFWwindow* window );
        
        void setupGeometry();

        void setVAO(unsigned int vao);
        void setShader(unsigned int shader);
        unsigned int getVAO() const;
        unsigned int getShader() const;

    private:
        unsigned int VAO = 0;
        unsigned int VBO = 0;
        unsigned int shaderProgram = 0;
};