    #define _USE_MATH_DEFINES
    #include <iostream>
    #include <thread>
    #include "headers/Canvas2D.h"
    #include <cmath>

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
            uniform vec4 uColor;

            void main() {
                FragColor = uColor;
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

        setShader(program);

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
    
        // renderizar tudo aqui

        setColor( 255, 0, 0, 1); // vermelho
        // mesh(-0.5f, -0.5f, 0.5f, -0.5f, 0.0f, 0.5f); // triângulo 1
        // triangle (0, 0, .1f);
        // rect( 0+xxx, 0+yyy, 100+www, 100+hhh );

        /*
        n+=1;
            rect( xxx, yyy, www, hhh );
            
            if( int(n) % 100000 == 0 ){
                std::cout << xxx << "\n";
                std::cout << yyy << "\n";
                std::cout << www << "\n";
                std::cout << hhh << "\n";
            }
        */

        rect( 0, 0, 100, 100 );

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

