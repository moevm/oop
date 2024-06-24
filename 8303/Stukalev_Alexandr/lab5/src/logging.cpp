#include "logging.h"
#include <iostream>

bool Logging::checkOpen()
{
    return fileOpen;
}
void Logging::loggingToFile(std::string & str)
{
    if (!fileOpen)
    {
        file = new File("logs.txt");
        fileOpen = true;
    }
    file->write(&str[0]);
}

void Logging::loggingToConsole(std::string& str)
{
    std::cout << str;
}

void Logging::fileClose()
{
    file->~File();
}

void Logging::setOpen(bool t)
{
    fileOpen = t;
}


void LoggingProxy::logUnitCreate(Unit* unit)
{
    std::string str = Adapter::adaptUnitCreate(unit);
    log(str);
}

void LoggingProxy::logUnitMove(Unit* unit, int x, int y)
{
    std::string str = Adapter::adaptUnitMove(unit, x, y);
    log(str);
}

void LoggingProxy::logUnitRemove(Unit* unit)
{
    std::string str = Adapter::adaptUnitCreate(unit);
    log(str);
}

void LoggingProxy::logUnitAttacked(Unit* unit)
{
    std::string str = Adapter::adaptUnitUnderAttack(unit);
    log(str);
}

void LoggingProxy::logBaseCreate(Base* base)
{
    std::string str = Adapter::adaptBaseCreate(base);
    log(str);
}

void LoggingProxy::logBaseAttacked(Base* base)
{
    std::string str = Adapter::adaptBaseUnderAttack(base);
    log(str);
}

void LoggingProxy::logGameover(Base* base)
{
    std::string str = Adapter::adaptGameOver(base);
    log(str);
}

void LoggingProxy::logOff()
{
    isLogging = false;
    logInFile = false;
    if(Logging::checkOpen())
    {
        Logging::fileClose();
        Logging::setOpen(false);
    }
    logInConsole = false;

}


void LoggingProxy::logToFile()
{
    isLogging = true;
    logInConsole = true;
    logInFile = false;
}

void LoggingProxy::logToConsole()
{
    isLogging = true;
    logInConsole = true;
    logInFile = false;
}

void LoggingProxy::log(std::string& str)
{
    if(!isLogging)
        return;
    if(logInConsole)
    {
        Logging::loggingToConsole(str);
    }
    if(logInFile)
    {
        Logging::loggingToFile(str);
    }
}





