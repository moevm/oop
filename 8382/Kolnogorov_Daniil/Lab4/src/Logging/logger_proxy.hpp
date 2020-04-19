#pragma once

#include "formatter_empty.hpp"
#include "logger.hpp"
#include "logger_empty.hpp"
#include <string>

using namespace std;

class LoggerProxy {
public:
    LoggerProxy()
        : logger(new LoggerEmpty()), formatter(new FormatterEmpty()) {}
    ~LoggerProxy() {
        delete logger;
        delete formatter;
    }

    void set_logger(Logger* logger) {
        delete this->logger;
        this->logger = logger;
    };

    void set_formatter(LogFormatter* formatter) {
        delete this->formatter;
        this->formatter = formatter;
    };

    friend LoggerProxy& operator<<(LoggerProxy& logger, const string& str) {
        logger.log(str);
        return logger;
    }

    friend LoggerProxy& operator<<(LoggerProxy& logger, const unsigned value) {
        logger.log(to_string(value));
        return logger;
    }

    friend LoggerProxy& operator<<(LoggerProxy& logger,
                                   const Logger::Endl&) {
        logger << "\n";
        logger.print_formatted = true;
        return logger;
    }

private:
    Logger* logger;
    LogFormatter* formatter;
    bool print_formatted = true;

    void log(const string& str) {
        if (print_formatted) {
            logger->log(formatter->format(str));
            print_formatted = false;
        } else {
            logger->log(str);
        }
    }
};
