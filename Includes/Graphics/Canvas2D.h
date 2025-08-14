#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Image.h"
#include "Shaders.h"

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
    Shaders shaders;


    // unsigned int compileShader( unsigned int type, const char* source );
    // unsigned int createShaderProgram( unsigned int vertexShader, unsigned int fragmentShader );
    

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


    rgba hexToRgba( char* hex );

    Image loadTexture(const char* path);

    void drawImage( Image* img, float x, float y, float w, float h);
    
    void drawSprite( Image* img, float cx, float cy, float cw, float ch, float x, float y, float w, float h);

        private:
    unsigned int VAO = 0;
    unsigned int VBO = 0;

    
    float fillColor[4] = {1.0f, 0.2f, 0.5f, 1.0f}; 

    float canvasWidth;
    float canvasHeight;

};