
#include <windows.h>
#include <string>
#include "headers/Utils.h"

std::string Utils::getExecutablePath() {
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH); // pega o caminho completo do exe
    std::string path(buffer);
    size_t lastSlash = path.find_last_of("\\/");
    return path.substr(0, lastSlash); // pasta do exe
}

std::string Utils::pathIn( std::string path ){
    return getExecutablePath() + path;
}