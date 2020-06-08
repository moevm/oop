#ifndef BATTLEFORHONOUR_NOFORMAT_H
#define BATTLEFORHONOUR_NOFORMAT_H


#include "LogFormat.h"

class NoFormat: public LogFormat {

    std::string getFormatted(std::string &notFormatted) override{
        return notFormatted;
    }

};

#endif //BATTLEFORHONOUR_NOFORMAT_H
