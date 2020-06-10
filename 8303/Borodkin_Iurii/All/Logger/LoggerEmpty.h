#ifndef LOGGEREMPTY_H
#define LOGGEREMPTY_H

#include "Logger.h"

class LoggerEmpty : public ILogger
{
public:
    ILogger& operator<<(const std::string&) override;
};

#endif // LOGGEREMPTY_H
