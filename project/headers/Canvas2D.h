#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Image.h"

struct rgba {
    float r, g, b, a;
};

class Canvas2D {
    public:
    Canvas2D();
    
    float xxx;
    float yyy;
    float www;
    float hhh;
    float n;

    Image image;

    const char* vertexShaderSource;
    const char* fragmentShaderSource;
    const char* uTexture;
    const char* textureVertexShader;
    const char* textureFragmentShader;

    unsigned int compileShader( unsigned int type, const char* source );
    unsigned int createShaderProgram( unsigned int vertexShader, unsigned int fragmentShader );
    
    void setVAO(unsigned int vao);
        void setShader(unsigned int shader);
        unsigned int getVAO() const;
        unsigned int getShader() const;


    void renderConstructor();
    void renderConfigs( GLFWwindow* window );
    void render( GLFWwindow* window );

    void setCanvasSize( float w, float h );

    float toNdcX( float x );
    float toNdcY( float y );

    
    void setColor( float r, float b, float g, float a );

    void mesh( float x1, float y1, float x2, float y2, float x3, float y3 );

    void triangle( float x, float y, float size );

    void rect( float x, float y, float w, float h);

    void square( float x, float y, float size );

    void drawImage( unsigned int textureID, float x, float y, float w, float h,
                        float u1, float v1, float u2, float v2 );
    rgba hexToRgba( char* hex );

    Image loadTexture(const char* path);

    void drawImage(unsigned int texture, float x, float y, float w, float h);
    
    void drawSprite( Image img, float cx, float cy, float cw, float ch, float x, float y, float w, float h);

    private:
        unsigned int VAO = 0;
        unsigned int VBO = 0;
        unsigned int shaderProgram = 0;
        unsigned int textureShader;
        
        float fillColor[4] = {1.0f, 0.2f, 0.5f, 1.0f}; 

        float canvasWidth;
        float canvasHeight;

};