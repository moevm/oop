#ifndef LOGSWITCH_H
#define LOGSWITCH_H

#include <string>
#include <iostream>
#include "FileRAII.h"

class LogSwitch{

protected:
    void printConsole(std::string message){
        std::cout<<"<log: >"<<message<<std::endl;
    }

    void printFile(std::string message){
        FileRAII file("Logs.txt", "log");
        file.write("<log:> " + message);
    }

};

#endif // LOGSWITCH_H
