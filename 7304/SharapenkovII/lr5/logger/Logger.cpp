//
// Created by smokfyz on 19.05.19.
//

#include "Logger.h"


Logger::Logger(unsigned cs) {
    logger = unique_ptr<LoggerInterface>(nullptr);

    cached = 0;
    logging = 0;
    cache_size = cs;
}

Logger& Logger::getLogger() {
    static Logger instance;

    return instance;
}

void Logger::setLogger(unique_ptr<LoggerInterface> &&l) {
    logger.swap(l);
}

void Logger::write(string str) {
    if(!logging) return;

    if(cached && cache.size() < cache_size) {
        cache.push_back(str);
    } else if(cached) {
        for(auto &s : cache)
            logger->write(s);
        cache.clear();
        cache.push_back(str);
    }

    if(!cached)
        logger->write(str);
}

string Logger::readline() {
    return logger->readline();
}

string Logger::read() {
    return logger->read();
}

void Logger::cachedMode(bool) {
    cached = !cached;
}

void Logger::loggingMode(bool) {
    logging = !logging;
}

bool Logger::getCached() {
    return cached;
}

bool Logger::getLogging() {
    return logging;
}


FileLogger::FileLogger(string file_name) {
    ilog_file.open(file_name);
    olog_file.open(file_name);
}

FileLogger::~FileLogger() {
    ilog_file.close();
    olog_file.close();
}

void FileLogger::write(string str) {
    olog_file << str << endl;
    olog_file.flush();
}

string FileLogger::readline() {
    string line;

    getline(ilog_file, line);

    return line;
}

string FileLogger::read() {
    string line;
    stringstream result;

    while(getline(ilog_file, line))
        result << line;

    return result.str();
}