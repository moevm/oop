#ifndef BATTLEFORHONOUR_LOGFORMAT_H
#define BATTLEFORHONOUR_LOGFORMAT_H


#include <string>

class LogFormat {

public:
    virtual std::string getFormatted(std::string &notFormatted)=0;
};

#endif //BATTLEFORHONOUR_LOGFORMAT_H
