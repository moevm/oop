#ifndef BATTLEFORHONOUR_FILELOGGER_H
#define BATTLEFORHONOUR_FILELOGGER_H


#include <fstream>
#include "Logger.h"

class FileLogger: public Logger {

private:

    std::ofstream fileStream;

public:

    explicit FileLogger(const std::string& filePath): fileStream(filePath){}

    ~FileLogger() override {
        fileStream.close();
    }

    void log(std::string &fs) override{
        fileStream << fs;
    }

    void log(Log::LogEnd &l) override{
        fileStream.flush();
    }

};


#endif //BATTLEFORHONOUR_FILELOGGER_H
