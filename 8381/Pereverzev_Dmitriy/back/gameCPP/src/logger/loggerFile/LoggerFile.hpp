
#ifndef LoggerFile_hpp
#define LoggerFile_hpp

#include <node.h>
#include <fstream>
#include "../Logger.hpp"

class LoggerFile : public Logger
{
private:
    std::ofstream fileLog;

public:
    LoggerFile(std::string filename);
    ~LoggerFile();

    void printLog(std::string strLog) override;
    
};

#endif /* LoggerFile_hpp */
