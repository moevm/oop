#ifndef BATTLEFORHONOUR_CMDLOGGER_H
#define BATTLEFORHONOUR_CMDLOGGER_H


#include <iostream>
#include "Logger.h"

class CmdLogger: public Logger {

public:

    void log(std::string &stream) override{
        std::cout << stream;
    }

};


#endif //BATTLEFORHONOUR_CMDLOGGER_H
