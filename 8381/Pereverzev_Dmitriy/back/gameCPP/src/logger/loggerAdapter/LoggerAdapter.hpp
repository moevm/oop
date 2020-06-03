
#ifndef LoggerAdapter_hpp
#define LoggerAdapter_hpp

#include <node.h>
#include <chrono>
#include <ctime>
#include <fstream>

#include "../../simplifiedConverter/SimplifiedConverter.hpp"

class LoggerAdapter : public SimplifiedConverter
{
private:
    bool status = false;

public:
    LoggerAdapter(bool status);
    LoggerAdapter();
    std::string
    adaptFormat(v8::Local<v8::Object> objLog);
    bool getStatus();
    void setStatus(bool status);
};

#endif /* LoggerAdapter_hpp */
