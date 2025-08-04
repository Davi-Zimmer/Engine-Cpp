#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <functional>
#include "headers/Engine.h"
#include "headers/Interpreter.h"


std::vector<std::string> splitCommand( const std::string& stringCommand ) {
    std::vector<std::string> args;
    std::istringstream iss(stringCommand);
    std::string arg;
    while (iss >> arg) {
        args.push_back(arg);
    }
    return args;
}

bool isValidNumberString( std::string str ){
    return (
        str.find_first_not_of("0123456789") == std::string::npos
    );
}

std::string lowerString(const std::string& str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

bool includes( std::vector< std::string > args, std::string cmd ){
    return lowerString( args[0] ) == lowerString( cmd );
}

template<typename T>
void printLine(T line) {
    std::cout << line << std::endl;
}

Interpreter::Interpreter( Engine e, GLFWwindow* wGl ){
    engine = e;
    winGL = wGl;
}

void Interpreter::getFps(){

    printLine( engine.getFpsTarget() );
    
}

void Interpreter::setFps( std::string stringFps ){

    if( !isValidNumberString( stringFps ) ) {

        printLine( "fps alvo invalido" );

        return;
    }

    int value = std::stoi( stringFps );
    
    engine.setFpsTarget( value );

    getFps();
}

void Interpreter::resizeWin ( std::vector< std::string > args ){

    if( args.size() < 2 ){
        printLine("sem parametros suficiente. deve ter altura e largura");
        return;
    }

    std::string widthString  = args[ 1 ];
    std::string heightString = args[ 2 ];

    int width;
    int height;

    if( widthString == "~") glfwGetWindowSize( winGL, &width, NULL );

    else if( isValidNumberString( widthString ) ) width = std::stoi( widthString );
    
    else {
        std::cout << "w invalido: " << width << std::endl;
        return;
    };  


    if( heightString == "~") glfwGetWindowSize( winGL, NULL, &height );
   
    else if( isValidNumberString( heightString ) ) height = std::stoi( heightString );

    else {
        std::cout << "w invalido: " << width << std::endl;
        return;
    }

    glfwSetWindowSize( winGL, width, height );

    glViewport(0, 0, width, height);

    std::cout << "w:" << width << "," "h:" << height << std::endl;
}

/*
Interpreter::
*/




void Interpreter::start()
{
    std::string cmd;

    while( true )
    {   
        std::cout << ">";

        std::getline( std::cin, cmd );

        if( cmd == "exit" ) break;

        std::vector< std::string > args = splitCommand( cmd );

        std::function<bool(std::string)> isCommand = ([&args]( std::string command ){
            return includes( args, command );
            std::cout << args[0] << "," << command << "\n";
        });

        if( isCommand("getFps") ) getFps(); else
        
        if( isCommand("setFps") ) setFps( args[1] ); else 

        if( isCommand("winSize") ) resizeWin( args ); else 

        if( isCommand("cls") || isCommand("clear") ) system("cls");
         
    }

}
