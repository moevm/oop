#include "LoggerFile.h"
#include <QDebug>

LoggerFile::LoggerFile(const std::string &path) : file(path)
{}

ILogger& LoggerFile::operator<<(const std::string& str)
{   
    file << str + '\n';
    return *this;
}

LoggerFile::~LoggerFile()
{
    file.close();
}
