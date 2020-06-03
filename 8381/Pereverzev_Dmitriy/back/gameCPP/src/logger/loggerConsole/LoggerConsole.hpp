
#ifndef LoggerConsole_hpp
#define LoggerConsole_hpp

#include <iostream>
#include <node.h>
#include "../Logger.hpp"

class LoggerConsole : public Logger
{
public:
    void printLog(std::string strLog) override;
    
};

#endif /* LoggerConsole_hpp */
