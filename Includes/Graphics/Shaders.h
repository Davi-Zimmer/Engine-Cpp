#pragma once


#include <functional>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Shaders {

    unsigned int VAO = 0;
    unsigned int VBO = 0;


    const char* uTexture;

    public:
    
    Shaders();
    
    const char* getVertexShaderSource();

    const char* getFragmentShaderSource();

    const char* getTextureVertexShader();

    const char* getTextureFragmentShader();

    unsigned int compileShader( unsigned int type, const char* source );
    unsigned int createShaderProgram( unsigned int vertexShader, unsigned int fragmentShader );


    void         setVAO(unsigned int vao);
    void         setShader(unsigned int shader);
    unsigned int getVAO() const;
    unsigned int getShader() const;
    

    void updateShaders( std::function<void()> renderCallback );

    void setTexture( unsigned int texture );

    void init();

    unsigned int getShaderProgram();
    unsigned int getTextureShader();

    const char* vertexShaderSource;
    const char* fragmentShaderSource;
    const char* textureVertexShader;
    const char* textureFragmentShader;

    unsigned int shaderProgram;
    unsigned int textureShader;
   
};