#include "LoggerProxy.hpp"

LoggerProxy::LoggerProxy(std::string loggerType, std::string filename)
{
    this->logger = new LoggerFile(filename + ".csv");
    active = true;
    adapter = new LoggerAdapter(true);
}
LoggerProxy::LoggerProxy(std::string loggerType)
{
    this->logger = new LoggerConsole();
    active = true;
    adapter = new LoggerAdapter(false);
}
LoggerProxy::LoggerProxy()
{
    logger = nullptr;
    active = false;
    adapter = new LoggerAdapter(false);
}
LoggerProxy::~LoggerProxy()
{
    delete logger;
    delete adapter;
}

void LoggerProxy::setLogger(std::string loggerType, std::string filename)
{
    if (loggerType == "file")
    {
        if (logger == nullptr)
            delete logger;
        this->logger = new LoggerFile(filename + ".csv");
        active = true;
    }
    else
        setLogger(loggerType);
}

void LoggerProxy::setLogger(std::string loggerType)
{
    if (loggerType == "console")
    {
        if (logger == nullptr)
            delete logger;
        this->logger = new LoggerConsole();
        active = true;
    }
    else if (loggerType == "empty_")
    {
        if (logger == nullptr)
            delete logger;
        logger = nullptr;
        active = false;
    }
}

void LoggerProxy::setAdapter(LoggerAdapter *adapter)
{
    this->adapter = adapter;
}
LoggerAdapter LoggerProxy::getAdapter()
{
    return this->adapter;
}

void LoggerProxy::printLog(std::string strLog)
{
    logger->printLog(strLog);
}

void LoggerProxy::printLog(v8::Local<v8::Object> data)
{
    printLog(adapter->getStatus() ? adapter->adaptFormat(data) : adapter->JSONStringified(data));
}

void operator<<(LoggerProxy *logger, v8::Local<v8::Object> data)
{
    
        
    logger->printLog(logger->adapter->getStatus() ? logger->adapter->adaptFormat(data) : logger->adapter->JSONStringified(data));
}

void LoggerProxy::eventHandler(Event *event)
{

    
    v8::Local<v8::Object> objResponse = Nan::New<v8::Object>();

    SetObjProperty(objResponse, "logType", event->getSEventId());
    SetObjProperty(objResponse, "data", event->getData());

    this << objResponse;
    
    
}