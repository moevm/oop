#ifndef LOGGING_H
#define LOGGING_H
#include <string>
#include "adapter.h"
#include "file.h"
class Logging
{
    static bool fileOpen;
    static File* file;
public:
    static bool checkOpen();
    static void loggingToFile(std::string&);
    static void loggingToConsole(std::string&);
    static void fileClose();
    static void setOpen(bool);
    Logging(){}
};

class LoggingProxy
{
    friend class Logging;
    static bool isLogging;
    static bool logInFile;
    static bool logInConsole;
    static void log(std::string&);
    static void log(std::ostringstream&);
public:
    LoggingProxy();
    static void logUnitCreate(Unit*);
    static void logUnitMove(Unit*, int, int);
    static void logUnitRemove(Unit*);
    static void logUnitAttacked(Unit*);
    static void logBaseCreate(Base*);
    static void logBaseAttacked(Base*);
    static void logGameover(Base*);
    static void logOff();
    static void logToFile();
    static void logToConsole();
    bool isOn();
};

#endif // LOGGING_H
