#define _USE_MATH_DEFINES
#define STB_IMAGE_IMPLEMENTATION

#include "../../Includes/Graphics/Shaders.h"
#include <iostream>

Shaders::Shaders(){
    vertexShaderSource = getVertexShaderSource();
    fragmentShaderSource = getFragmentShaderSource();
    textureVertexShader = getTextureVertexShader();
    textureFragmentShader = getTextureFragmentShader();

    
}

const char* Shaders::getVertexShaderSource(){
    return R"(
        #version 330 core
        layout(location = 0) in vec2 aPos;

        void main() {
            gl_Position = vec4(aPos, 0.0, 1.0);
        }
    )";

}

const char* Shaders::getFragmentShaderSource(){
    return R"(
        #version 330 core
        out vec4 FragColor;
        uniform vec4 uColor;

        void main() {
            FragColor = uColor;
        }
    )";
}

const char* Shaders::getTextureVertexShader(){
    return R"(
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
}

const char* Shaders::getTextureFragmentShader(){
    return R"(
        #version 330 core
        in vec2 TexCoord;
        out vec4 FragColor;

        uniform sampler2D uTexture;

        void main() {
            FragColor = texture(uTexture, TexCoord);
        }
    )";
}

unsigned int Shaders::compileShader(unsigned int type, const char* source) {
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

unsigned int Shaders::createShaderProgram(unsigned int vertexShader, unsigned int fragmentShader) {
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

void Shaders::init(){

    unsigned int vShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    unsigned int fShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
    unsigned int program = createShaderProgram(vShader, fShader);

    unsigned int texVert = compileShader(GL_VERTEX_SHADER, textureVertexShader);
    unsigned int texFrag = compileShader(GL_FRAGMENT_SHADER, textureFragmentShader);
    textureShader = createShaderProgram(texVert, texFrag);

    setShader(program);

}





void         Shaders::setVAO(unsigned int vao) { VAO = vao; }
void         Shaders::setShader(unsigned int shader) { shaderProgram = shader; }
unsigned int Shaders::getVAO() const { return VAO; }
unsigned int Shaders::getShader() const { return shaderProgram; }


void Shaders::setTexture( unsigned int texture ){
    // texture
}


unsigned int Shaders::getShaderProgram(){
    return shaderProgram;
}


unsigned int Shaders::getTextureShader(){
    return textureShader;
}