#ifndef LOGGER_H
#define LOGGER_H

#include <sstream>

class Logger
{
    std::stringstream buffer;

public:
    Logger(void) = default;

    Logger& operator<<(const std::string& str);

    friend std::ostream& operator<<(std::ostream& os, Logger& logger);

    bool empty() const;
};

#endif // LOGGER_H
