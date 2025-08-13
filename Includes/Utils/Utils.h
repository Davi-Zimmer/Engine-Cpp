#pragma once
#include <windows.h>
#include <string>

class Utils {
    public:
    static std::string getExecutablePath();
    static std::string pathIn( std::string path  );
};