#ifndef ILOGGER_H
#define ILOGGER_H

#include <memory>
#include <iostream>
#include <string>
#include <fstream>

#include "logfunctionality.h"

class Time;

class ILogger
{
public:
    virtual ~ILogger() = default;
    virtual bool isActive() = 0;
    virtual eLOGGER_TYPE getType() = 0;
    virtual void printLog(std::string outInf) = 0;  // just str print (using method below)
    virtual void print() = 0;                       // for '<<' overload
    virtual void printCurrTime() = 0;
    virtual void printProgWorkingTime() = 0;

    // operator '<<' overload stuff (we can't create abstract class or use it from friend, because interface)
    virtual std::shared_ptr<Time>& getTime() = 0;
    virtual std::string getLogInf() const = 0;
};

#endif // ILOGGER_H
