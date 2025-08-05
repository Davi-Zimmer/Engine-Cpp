#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Canvas2D {
    public:
    Canvas2D();

    const char* vertexShaderSource;
    const char* fragmentShaderSource;
    
    unsigned int compileShader( unsigned int type, const char* source );
    unsigned int createShaderProgram( unsigned int vertexShader, unsigned int fragmentShader );
    
    void setVAO(unsigned int vao);
        void setShader(unsigned int shader);
        unsigned int getVAO() const;
        unsigned int getShader() const;


    
    void renderConstructor();
    void render();
    void setupGeometry();
    private:
        unsigned int VAO = 0;
        unsigned int VBO = 0;
        unsigned int shaderProgram = 0;

};