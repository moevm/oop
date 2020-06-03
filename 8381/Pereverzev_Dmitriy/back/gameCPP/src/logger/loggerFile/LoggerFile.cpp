
#include "LoggerFile.hpp"

LoggerFile::LoggerFile(std::string filename)
{
    this->fileLog.open("./logs/" + filename, std::ios::app);
}
LoggerFile::~LoggerFile()
{
    fileLog.close();
}

void LoggerFile::printLog(std::string strLog)
{
    fileLog << strLog << std::endl;
}