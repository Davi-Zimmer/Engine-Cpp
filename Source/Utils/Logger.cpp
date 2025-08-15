#include <iostream>
#include "../../Includes/Utils/Logger.h"


Logger* Logger::Instance;

Logger::Logger(){}

Logger& Logger::GetInstance(){

    if( Instance == nullptr ) Instance = new Logger();

    return *Instance;

}


