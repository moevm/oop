#ifndef BATTLEFORHONOUR_LOGGER_H
#define BATTLEFORHONOUR_LOGGER_H

#include <string>
#include "LogEnd.h"

class Logger {

public:
    virtual void log(std::string &str)=0;
    virtual void log(Log::LogEnd &l){}
    virtual ~Logger(){}
};

#endif //BATTLEFORHONOUR_LOGGER_H
