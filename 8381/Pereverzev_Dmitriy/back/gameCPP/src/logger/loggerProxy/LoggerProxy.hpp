
#ifndef LoggerProxy_hpp
#define LoggerProxy_hpp

#include <string>
#include <node.h>

#include "../Logger.hpp"
#include "../loggerFile/LoggerFile.hpp"
#include "../loggerConsole/LoggerConsole.hpp"
#include "../loggerAdapter/LoggerAdapter.hpp"

class LoggerProxy : public Logger
{
private:
    Logger *logger;
    LoggerAdapter *adapter;
    bool active = false;

    void eventHandler(Event *event);

public:
    LoggerProxy(std::string loggerType, std::string filename);
    LoggerProxy(std::string loggerType);
    LoggerProxy();
    ~LoggerProxy();

    void setLogger(std::string loggerType, std::string filename);
    void setLogger(std::string loggerType);
    void setAdapter(LoggerAdapter *adapter);
    LoggerAdapter getAdapter();

    friend void operator<<(LoggerProxy *logger, v8::Local<v8::Object> data);
    void printLog(std::string strLog) override;
    void printLog(v8::Local<v8::Object> data);
    
};

#endif /* LoggerProxy_hpp */
