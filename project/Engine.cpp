#include <iostream>
#include <thread>
#include "./headers/Engine.h"


const char* vertexShaderSource = R"(
#version 330 core
layout(location = 0) in vec2 aPos;

void main() {
    gl_Position = vec4(aPos, 0.0, 1.0);
}
)";

const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;

void main() {
    FragColor = vec4(1.0, 0.2, 0.5, 1.0); // rosa
}
)";



unsigned int compileShader(unsigned int type, const char* source) {
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

unsigned int createShaderProgram(unsigned int vertexShader, unsigned int fragmentShader) {
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



Engine::Engine(){

    setFpsTarget( 30 );
    
    timePerFrame = .0f / targetFps;
    
    fpsCounter =.0f;
    framesRendered = 0;

}

int Engine::setFpsTarget( int fps )
{
    targetFps = fps;
    return targetFps;
}

int Engine::getFpsTarget()
{
    return targetFps;
}


void Engine::frameSkipper( GLFWwindow* window )
{

    auto  lastTime = std::chrono::high_resolution_clock::now();
    auto  fpsTimer = std::chrono::high_resolution_clock::now();
    float accumulator = .0f;
    
    renderConstructor();


    while(!glfwWindowShouldClose(window))
    {
        // Medir tempo desde o último loop
        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> delta = currentTime - lastTime;
        lastTime = currentTime;

        accumulator += delta.count();
        fpsCounter += delta.count();

        // FPS real
        if (fpsCounter >= 1.0f) {
            // std::cout << "FPS: " << framesRendered << std::endl;
            fpsCounter = 0.0f;
            framesRendered = 0;
        }

        // Se passou tempo suficiente, renderiza um frame
        if (accumulator >= timePerFrame) {
            accumulator -= timePerFrame;
            framesRendered++;
        }
        
        render( window );

    }


}


void Engine::renderConstructor(){

    unsigned int vShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    unsigned int fShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    unsigned int program = createShaderProgram(vShader, fShader);

    setShader(program);
    setupGeometry();

}

void Engine::render( GLFWwindow* window ){
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
}


void         Engine::setVAO(unsigned int vao) { VAO = vao; }
void         Engine::setShader(unsigned int shader) { shaderProgram = shader; }
unsigned int Engine::getVAO() const { return VAO; }
unsigned int Engine::getShader() const { return shaderProgram; }


void Engine::setupGeometry() {
    float vertices[] = {
        // posições (x, y)
        -0.1f, -0.1f,
        0.1f, -0.1f,
        0.0f,  0.1f
    };

    unsigned int vao, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    setVAO(vao);
}