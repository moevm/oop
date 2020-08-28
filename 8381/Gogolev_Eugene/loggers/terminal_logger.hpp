#ifndef GOGOLEV_STRATEGY_TERMINAL_LOGGER_HPP
#define GOGOLEV_STRATEGY_TERMINAL_LOGGER_HPP

#include "logger.hpp"

class TerminalLogger : public Logger {
public:
    void log(const string &message) override;
};


#endif //GOGOLEV_STRATEGY_TERMINAL_LOGGER_HPP
