//
// Created by anton on 12.04.2020.
//

#ifndef OOP_1_PROXYLOGGER_H
#define OOP_1_PROXYLOGGER_H


#include "Logger.h"

class ProxyLogger: public Logger {
public:
    void switchLogStream(std::string mode);

    void turnOnOffLog(std::string mode);
};


#endif //OOP_1_PROXYLOGGER_H
