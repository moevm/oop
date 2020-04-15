#ifndef LOGGER_H
#define LOGGER_H
#include "basicinterfaces.h"
#include <fstream>

class Time
{
public:
    Time() {
        time_t timer;
        time(&timer);
        lastTime = localtime(&timer);
    }

    void update() {
        time_t timer;
        time(&timer);
        lastTime = localtime(&timer);
    }

    friend std::ostream& operator<<(std::ostream& os, Time& tm);
private:
    tm *lastTime;
};

class TerminalLogger : public ILogger
{
public:
    TerminalLogger();

    void printTime();
    void printLog(std::string info);
    void print();
    bool isActive();

    Time *getLocalTime() const;
    std::string getInfo() const;
    void setInfo(const std::string &value);

    ~TerminalLogger();
    friend std::ostream& operator<<(std::ostream& os, ILogger& tl);

private:
    Time *localTime;
    std::string info;
};

class FileLogger : public ILogger
{
public:
    FileLogger(std::string fileName);

    void printTime();
    void printLog(std::string info);
    void print();
    bool isActive();

    std::string getInfo() const;
    void setInfo(const std::string &value);
    Time *getLocalTime() const;

    friend std::ostream& operator<<(std::ostream& os, ILogger& tl);
    ~FileLogger();

private:
    Time *localTime;
    std::string info;
    std::ofstream fout;
};

class ProxyLogger : public ILogger
{
public:
    ProxyLogger(LoggerType type);
    void print();
    void printTime();
    void printLog(std::string output);
    bool isActive();

    std::string getInfo() const;
    void setInfo(const std::string &value);
    Time *getLocalTime() const;

    ~ProxyLogger();
private:
    ILogger *logger;
};

#endif // LOGGER_H
