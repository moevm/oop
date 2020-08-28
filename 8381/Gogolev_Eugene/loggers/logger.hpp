#ifndef GOGOLEV_STRATEGY_LOGGER_HPP
#define GOGOLEV_STRATEGY_LOGGER_HPP

#include "../stl.hpp"


class Logger {
public:
    virtual ~Logger() = default;
    virtual void log(const string &message) = 0;
};


#endif //GOGOLEV_STRATEGY_LOGGER_HPP
