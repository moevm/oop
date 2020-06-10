#include "Logger.h"

LoggerProxy::LoggerProxy(ILogger* _log) : log(_log)
{}

ILogger& LoggerProxy::operator<<(const std::string &str)
{

    (*log) << target->request(str);
    return (*log);
}

void LoggerProxy::setLogger(ILogger* l)
{
    delete log;
    log = l;
}

void LoggerProxy::setTarget(Target* t)
{
    delete target;
    target = t;
}

LoggerProxy::~LoggerProxy()
{
    delete log;
    delete target;
}
