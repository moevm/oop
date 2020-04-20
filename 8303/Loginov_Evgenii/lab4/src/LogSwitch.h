#ifndef LOGSWITCH_H
#define LOGSWITCH_H

#include <string>
#include <iostream>
#include "FileRAII.h"

class LogSwitch{
    FileRAII* file;
protected:
    void printConsole(std::string message){
        std::cout<<"<log: >"<<message<<std::endl;
    }

    void printFile(std::string message){
        file = new FileRAII("Logs.txt");
        file->write("<log:> " + message);
        delete file;
    }

};

#endif // LOGSWITCH_H
