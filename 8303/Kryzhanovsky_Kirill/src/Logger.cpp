//
// Created by therealyou on 31.05.2020.
//

#include "Logger.h"

Logger::Logger() : loggerOn(false), writeToFile(false) {}

void Logger::print(std::string message) {
    if (!loggerOn)
        return;
    if (writeToFile) {
        file = new File("logs.txt");
        file->write(message);
        delete file;
    } else {
        std::cout << "log message: " << message;
    }
}
