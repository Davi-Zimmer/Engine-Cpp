#pragma once

class Logger {

    static Logger* Instance; 

    static Logger& GetInstance();

    private:
        Logger();

};