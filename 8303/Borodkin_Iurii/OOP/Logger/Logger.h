#ifndef LOGGER_H
#define LOGGER_H
#include <ostream>
#include "Adapter/Adapter.h"

class ILogger
{
public:
    virtual ILogger& operator<<(const std::string&) = 0;
    virtual ~ILogger() = default;
};

class LoggerProxy : public ILogger
{
public:
    LoggerProxy(ILogger* = nullptr);
    ILogger& operator<<(const std::string&) override;
    void setLogger(ILogger*);
    void setTarget(Target*);
    ~LoggerProxy() override;
private:
    ILogger* log = nullptr;
    Target* target = nullptr;
};

#endif // LOGGER_H
