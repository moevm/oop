#ifndef BATTLEFORHONOUR_LOGPROXY_H
#define BATTLEFORHONOUR_LOGPROXY_H

#include "NoLogger.h"
#include "LogString.h"
#include <string>
#include <iostream>

class LogProxy {

private:

    Logger *logger;
    LogString *logString;
    bool firstLine = true;

    void log(std::string s){
        if (firstLine) {
            std::string toLog = logString->getString(s);
            logger->log(toLog);
            firstLine = false;
        } else{
            logger->log(s);
        }
    }

public:

    LogProxy():
            logger(new NoLogger()){}

    ~LogProxy(){
        delete logger;
        delete logString;
    }

    friend LogProxy& operator<< (LogProxy &logger, const std::string &s){
        logger.log(s);
        return logger;
    }

    friend LogProxy& operator<< (LogProxy &logger, const int i){
        logger.log(std::to_string(i));
        return logger;
    }

    friend LogProxy& operator<< (LogProxy &logger, const Log::LogEnd &l){
        logger.log("\n");
        logger.firstLine = true;
        return logger;
    }

    void setLogFormat(Logger *tmp){

        delete logger;
        logger = tmp;
    }

    void setLogStrOutput(LogString *tmp){
        delete logString;
        logString = tmp;
    }

};


#endif //BATTLEFORHONOUR_LOGPROXY_H
