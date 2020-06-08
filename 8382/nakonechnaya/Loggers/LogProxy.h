#ifndef OOP_LOGPROXY_H
#define OOP_LOGPROXY_H
#include "NoLogger.h"
#include "FileLogger.h"
#include "TerminalLogger.h"

class LogProxy : public Logger{
public:
    explicit LogProxy(LoggerType loggerType);
    ~LogProxy() = default;
    void print() final {if (logger) logger->print();};
    void setLog(std::string logString) final {logger->setLog(logString);};
    void addLog(std::string logString) final {logger->addLog(logString);};
    void setFormat(int format) final {logger->setFormat(format);};
    int getFormat() final { return logger->getFormat();};
private:
    Logger *logger;
};
#endif //OOP_LOGPROXY_H
