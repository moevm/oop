#include "LoggerEmpty.h"

ILogger& LoggerEmpty::operator<<(const std::string&)
{
    return *this;
}
