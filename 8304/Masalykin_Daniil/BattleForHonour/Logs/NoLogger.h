#ifndef BATTLEFORHONOUR_NOLOGGER_H
#define BATTLEFORHONOUR_NOLOGGER_H


#include "Logger.h"

class NoLogger: public Logger {

public:
    void log(std::string &s) override{
        return;
    }
};


#endif //BATTLEFORHONOUR_NOLOGGER_H
