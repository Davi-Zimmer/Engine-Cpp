#include <iostream>
#include "headers/Logger.h"


Logger::Logger(){}


Logger& Logger::GetInstance(){

    if( Instance == nullptr ) Instance = new Logger();

    return *Instance;

}