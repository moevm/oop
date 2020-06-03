#ifndef GOGOLEV_STRATEGY_LOGGER_PROXY_HPP
#define GOGOLEV_STRATEGY_LOGGER_PROXY_HPP

#include "logger.hpp"

class LoggerProxy : public Logger {
public:
    explicit LoggerProxy(Logger* concrete);
    void setChild(Logger* concrete);
    void log (const string& message) override;
private:
    Logger* child;
};


#endif //GOGOLEV_STRATEGY_LOGGER_PROXY_HPP
