#define _USE_MATH_DEFINES
#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <thread>
#include <cmath>
#include "headers/Canvas2D.h"
#include "./external/stb_image.h"
#include "./headers/Image.h"
#include "./headers/Matrix.h"

#include <string>
#include <windows.h>

std::string getExecutablePath() {
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH); // pega o caminho completo do exe
    std::string path(buffer);
    size_t lastSlash = path.find_last_of("\\/");
    return path.substr(0, lastSlash); // pasta do exe
}

Canvas2D::Canvas2D(): image(0, 0, 0) {
    
        vertexShaderSource = R"(
            #version 330 core
            layout(location = 0) in vec2 aPos;

            void main() {
                gl_Position = vec4(aPos, 0.0, 1.0);
            }
        )";

        fragmentShaderSource = R"(
            #version 330 core
            out vec4 FragColor;
            uniform vec4 uColor;

            void main() {
                FragColor = uColor;
            }
        )";


        textureVertexShader = R"(
            #version 330 core
            layout(location = 0) in vec2 aPos;
            layout(location = 1) in vec2 aTexCoord;

            uniform mat4 uTransform;  // nova linha

            out vec2 TexCoord;

            void main() {
                vec4 position = vec4(aPos, 0.0, 1.0);
                gl_Position = uTransform * position;
                TexCoord = aTexCoord;
            }

        )";

        textureFragmentShader = R"(
           #version 330 core
            in vec2 TexCoord;
            out vec4 FragColor;

            uniform sampler2D uTexture;

            void main() {
                FragColor = texture(uTexture, TexCoord);
            }
        )";

    xxx = 0;
    yyy = 0;
    www = 100;
    hhh = 100;
    n = 0;

}

unsigned int Canvas2D::compileShader(unsigned int type, const char* source) {
    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    // checagem de erro
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "Erro ao compilar " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") 
                << " shader:\n" << infoLog << std::endl;
    }

    
    return shader;
}

unsigned int Canvas2D::createShaderProgram(unsigned int vertexShader, unsigned int fragmentShader) {
    unsigned int program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << "Erro ao linkar programa:\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}


void         Canvas2D::setVAO(unsigned int vao) { VAO = vao; }
void         Canvas2D::setShader(unsigned int shader) { shaderProgram = shader; }
unsigned int Canvas2D::getVAO() const { return VAO; }
unsigned int Canvas2D::getShader() const { return shaderProgram; }

void Canvas2D::renderConstructor(){

    unsigned int vShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    unsigned int fShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
    unsigned int program = createShaderProgram(vShader, fShader);

    unsigned int texVert = compileShader(GL_VERTEX_SHADER, textureVertexShader);
    unsigned int texFrag = compileShader(GL_FRAGMENT_SHADER, textureFragmentShader);
    textureShader = createShaderProgram(texVert, texFrag);

    /*
    float dummy[] = {
        0.0f, 0.0f, 0.0f, 0.0f,  // espaço para 6 vértices com (x, y, u, v)
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(dummy), dummy, GL_DYNAMIC_DRAW);

    // posição: 2 floats
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // texcoord: 2 floats
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    */
    setShader(program);
    //std::string imgPath = getExecutablePath() + "\\test.png";
    std::string imgPath = getExecutablePath() + "\\tiles.png";

    image = loadTexture( imgPath.c_str() );

}


void Canvas2D::renderConfigs( GLFWwindow* window ){

    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);

    int colorLocation = glGetUniformLocation( shaderProgram, "uColor");
    glUniform4fv( colorLocation, 1, fillColor);

    render( window );

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();

}

void Canvas2D::render( GLFWwindow* window ) {
    
    // setColor(255, 0, 0, 1);
    // rect(100, 100, 100, 100);
    // drawImage( &image, 100, -100, 100, 100 );
    
    // drawSprite( &image, 0, 0, 20, 20, 0, 0, 100, 100 );

    // image.setRotationZ( image.getRotationZ() + .001f );
    // image.setRotationY( image.getRotationY() + .001f );
    // image.setRotationX( image.getRotationX() + .001f );

    drawSprite( &image, 128, 0, 32, 32, 0, 0, 100, 100 );
    
}


void Canvas2D::setCanvasSize( float w, float h ){
    glViewport(0, 0, w, h);
    canvasWidth = w;
    canvasHeight = h;

    std::cout << w << " " << h << "\n";

}

float Canvas2D::toNdcX( float x ){
    return (x / canvasWidth) * 2.0f - 1;
}

float Canvas2D::toNdcY( float y ){
    return  1 - (y / -canvasHeight) * 2.0f;
}

rgba Canvas2D::hexToRgba( char* hex ){

    throw "Not Implemented";

}


void Canvas2D::setColor( float r, float g, float b, float a ){
    fillColor[0] = r;
    fillColor[1] = g;
    fillColor[2] = b;
    fillColor[3] = a;
}

void Canvas2D::mesh( float x1, float y1, float x2, float y2, float x3, float y3 ){
    
    float vertices[] = {
        x1, y1, 
        x2, y2,
        x3, y3
    };

    unsigned int vao, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glUseProgram(shaderProgram);
    glUniform4fv(glGetUniformLocation(shaderProgram, "uColor"), 1, fillColor);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

}

void Canvas2D::triangle( float cx, float cy, float size ){
    float halfSize = size / 2.0f;

    float angle120 = M_PI * 2.0f / 3.0f;

    float x1 = cx;
    float y1 = cy + size / std::sqrt(3.0f);

    float x2 = cx - halfSize;
    float y2 = cy - size / (2.0f * std::sqrt(3.0f));

    float x3 = cx + halfSize;
    float y3 = y2;

    mesh(x1, y1, x2, y2, x3, y3);
}

void Canvas2D::rect( float x, float y, float w, float h){

    float x1 = toNdcX( x );
    float y1 = toNdcY( y );
    float x2 = toNdcX( x + w );
    float y2 = toNdcY( y );
    float x3 = toNdcX( x );
    float y3 = toNdcY( y - h );
    float x4 = toNdcX( x + w );
    float y4 = toNdcY( y - h );

    mesh(x1, y1, x2, y2, x3, y3);
    mesh(x2, y2, x3, y3, x4, y4);
}

void Canvas2D::square( float x, float y, float size ){
    rect( x, y, size, size );
}

Image Canvas2D::loadTexture(const char* path) {
    
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 4);
    if (!data) {
        std::cout << "Erro ao carregar imagem: " << path << "\n";
        

        return Image( 0, 0, 0 );
    }
    
    unsigned int texture;
    glGenTextures(1, &texture);
    // getchar();
    glBindTexture(GL_TEXTURE_2D, texture);
    stbi_set_flip_vertically_on_load(true);

    // Parâmetros da textura
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);     
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);     

    // Upload da textura para a GPU
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    Image img( texture, width, height );

    return img;
}

void Canvas2D::drawImage( Image* img, float x, float y, float w, float h ) {
    
    float u0 = 0.0f, u1 = 1.0f;
    float v0 = 1.0f, v1 = 0.0f;

    float vertices[] = {
        -1.0f,  1.0f, u0, v0,
         1.0f,  1.0f, u1, v0,
        -1.0f, -1.0f, u0, v1,
         1.0f, -1.0f, u1, v1
    };

    unsigned int indices[] = { 0, 1, 2, 1, 2, 3 };

    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    stbi_set_flip_vertically_on_load(true);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glUseProgram(textureShader);
    glBindTexture(GL_TEXTURE_2D, img->getTexture());

    float model[16];
    float scaleX = toNdcX(x + w) - toNdcX(x);
    float scaleY = toNdcY(y) - toNdcY(y + h);

    Matrix::CreateTransformMatrix(
        model,
        toNdcX(x + w / 2.0f),
        toNdcY(y - h / 2.0f),
        scaleX / 2.0f,
        scaleY / 2.0f,
        img->getRotationX(),
        img->getRotationY(),
        img->getRotationZ()
    );

    GLint transformLoc = glGetUniformLocation(textureShader, "uTransform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, model);

    glUniform1i(glGetUniformLocation(textureShader, "uTexture"), 0);
    glActiveTexture(GL_TEXTURE0);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Canvas2D::drawSprite( Image* img, float sx, float sy, float sw, float sh, float dx, float dy, float dw, float dh ) {
    // Tamanho total da imagem (sprite sheet)
    float texW = (float)img->getWidth();
    float texH = (float)img->getHeight();

    
    float u0 = sx / texW;
    float u1 = (sx + sw) / texW;

    float v0 = 1.0f - (sy / texH);
    float v1 = 1.0f - ((sy + sh) / texH);
    // Vertices com posições relativas ao centro (-1 a 1)
    float vertices[] = {
        -1.0f,  1.0f,  u0, v0,
         1.0f,  1.0f,  u1, v0,
        -1.0f, -1.0f,  u0, v1,
         1.0f, -1.0f,  u1, v1
    };

    unsigned int indices[] = { 0, 1, 2, 1, 2, 3 };

    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glUseProgram(textureShader);
    glBindTexture(GL_TEXTURE_2D, img->getTexture());

    // Calcula matriz de transformação usando a posição e tamanho de destino (dx,dy,dw,dh)
    float model[16];
    float scaleX = toNdcX(dx + dw) - toNdcX(dx);
    float scaleY = toNdcY(dy) - toNdcY(dy + dh); // lembra que y cresce pra baixo na tela

    Matrix::CreateTransformMatrix(
        model,
        toNdcX(dx + dw / 2.0f),
        toNdcY(dy - dh / 2.0f),
        scaleX / 2.0f,
        scaleY / 2.0f,
        img->getRotationX(),
        img->getRotationY(),
        img->getRotationZ()
    );

    GLint transformLoc = glGetUniformLocation(textureShader, "uTransform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, model);

    glUniform1i(glGetUniformLocation(textureShader, "uTexture"), 0);
    glActiveTexture(GL_TEXTURE0);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

