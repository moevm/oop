//
// Created by therealyou on 31.05.2020.
//

#ifndef LAB1_PROXYLOGGER_H
#define LAB1_PROXYLOGGER_H

#include "Logger.h"

class ProxyLogger : public Logger {
public:
    void switchLogStream(std::string mode);

    void turnOnOffLog(std::string mode);
};

#endif //LAB1_PROXYLOGGER_H
