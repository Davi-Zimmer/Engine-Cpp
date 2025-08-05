#include <iostream>
#include <thread>
#include "headers/Canvas2D.h"


Canvas2D::Canvas2D(){
    
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

        void main() {
            FragColor = vec4(1.0, 0.2, 0.5, 1.0); // rosa
        }
    )";

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

    setShader(program);
    setupGeometry();

}

void Canvas2D::render(){
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
}

void Canvas2D::setupGeometry() {
    float vertices[] = {
        -0.5f, -0.5f,
        0.5f, -0.5f,
        0.0f,  0.5f
    };

    unsigned int vao, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // layout(location = 0) no shader, 2 floats por vértice
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    setVAO(vao); // armazena o VAO na Engine
}