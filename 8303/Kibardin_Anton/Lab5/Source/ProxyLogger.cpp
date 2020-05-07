//
// Created by anton on 12.04.2020.
//

#include "ProxyLogger.h"

void ProxyLogger::switchLogStream(std::string mode) {
    if(mode == "console")
        this->writeToFile = false;
    else if (mode == "file")
        this->writeToFile = true;
}

void ProxyLogger::turnOnOffLog(std::string mode) {
    if(mode == "on")
        this->loggerOn = true;
    else if (mode == "off")
        this->loggerOn = false;
}