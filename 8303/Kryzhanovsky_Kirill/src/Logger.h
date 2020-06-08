//
// Created by therealyou on 31.05.2020.
//

#ifndef LAB1_LOGGER_H
#define LAB1_LOGGER_H


#include <string>
#include "File.h"

class Logger {
protected:
    bool writeToFile, loggerOn;
    File *file;


public:
    explicit Logger();

    void print(std::string);

    friend class ProxyLogger;
};

#endif //LAB1_LOGGER_H
