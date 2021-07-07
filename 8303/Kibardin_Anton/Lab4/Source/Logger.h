//
// Created by anton on 11.04.2020.
//

#ifndef OOP_1_LOGGER_H
#define OOP_1_LOGGER_H

#include <string>
#include "File.h"

class Logger {
protected:
    bool writeToFile, loggerOn;
    File* ptr;


public:
    explicit Logger();
    void print(std::string);

    friend class ProxyLogger;
};


#endif //OOP_1_LOGGER_H
