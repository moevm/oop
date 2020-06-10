#ifndef LOGGERFILE_H
#define LOGGERFILE_H
#include "Logger.h"
#include <fstream>

class LoggerFile : public ILogger
{
public:
    LoggerFile(const std::string &path);
    ILogger& operator<<(const std::string&) override;
    ~LoggerFile() override;
private:
    std::ofstream file;
};

#endif // LOGGERFILE_H
