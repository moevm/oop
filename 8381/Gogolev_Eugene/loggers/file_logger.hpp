#ifndef GOGOLEV_STRATEGY_FILE_LOGGER_HPP
#define GOGOLEV_STRATEGY_FILE_LOGGER_HPP

#include "logger.hpp"

class FileLogger : public Logger {
public:
    FileLogger(const string& fileName);
    void log (const string& message) override;

private:
    string fileName;
};

#endif //GOGOLEV_STRATEGY_FILE_LOGGER_HPP
