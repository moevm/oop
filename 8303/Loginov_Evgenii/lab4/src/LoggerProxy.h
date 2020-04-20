#ifndef LOGGERPROXY_H
#define LOGGERPROXY_H

#include <string>
#include <iostream>
#include "LogSwitch.h"
#include "FileRAII.h"

class LoggerProxy: LogSwitch{

public:
    LoggerProxy(){

    }

protected:
    void print(std::string log, bool consoleWrite, bool fileWrite){

        if (consoleWrite){
            printConsole(log);
        }
        if (fileWrite) {
            printFile(log);
        }
    }
};

#endif // LOGGERPROXY_H
