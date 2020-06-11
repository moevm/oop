//
// Created by anton on 11.04.2020.
//

#include "Logger.h"

Logger::Logger():loggerOn(false), writeToFile(false){}

void Logger::print(std::string message){
    if(!loggerOn)
        return;
    if(writeToFile)
    {
        ptr = new FileOut("logs.txt", "log");
        ptr->write(message);
        delete  ptr;
    } else
    {
        std::cout << "log message: " << message;
    }
}

