#include "logger.h"

std::ostream& operator<<(std::ostream& os, Time& tm)
{
    tm.update();
    os << tm.lastTime->tm_hour << ":" << tm.lastTime->tm_min << ":" << tm.lastTime->tm_sec;
    return os;
}

std::ostream &operator<<(std::ostream &os, ILogger &il)
{
    os << *(il.getLocalTime()) << " >> " << il.getInfo();
    return os;
}

//TERMINAL LOGGER

TerminalLogger::TerminalLogger()
{
    localTime = new Time;
}

void TerminalLogger::printTime()
{
    std::cout << *localTime << std::endl;
}

void TerminalLogger::printLog(std::string info)
{
    this->info = info;
    print();
}

void TerminalLogger::print()
{
    std::cout << *this << std::endl;
}

bool TerminalLogger::isActive()
{
    return true;
}

TerminalLogger::~TerminalLogger()
{
    std::cout << *localTime << " << Logger stopped\n";
    delete localTime;
}

Time *TerminalLogger::getLocalTime() const
{
    return localTime;
}

std::string TerminalLogger::getInfo() const
{
    return info;
}

void TerminalLogger::setInfo(const std::string &value)
{
    info = value;
}

//FILE LOGGER

FileLogger::FileLogger(std::string fileName)
{
    fout.open(fileName);
    if (!fout.is_open())
        throw std::runtime_error("File open failure");
    localTime = new Time;
}

void FileLogger::printTime()
{
    fout << *localTime;
}

void FileLogger::printLog(std::string info)
{
    this->info = info;
    print();
}

void FileLogger::print()
{
    fout << *this << "\n";
}

bool FileLogger::isActive()
{
    return true;
}

FileLogger::~FileLogger()
{
    fout << *localTime << " << Logger stopped\n";
    fout.close();
    delete localTime;
}


std::string FileLogger::getInfo() const
{
    return info;
}

void FileLogger::setInfo(const std::string &value)
{
    info = value;
}

Time *FileLogger::getLocalTime() const
{
    return localTime;
}

//PROXY LOGGER

ProxyLogger::ProxyLogger(LoggerType type)
{
    if (type == NO_LOGGER)
        logger = nullptr;
    else if (type == TO_TERMINAL)
        logger = new TerminalLogger;
    else if (type == TO_FILE)
        logger = new FileLogger(LOGFILE);
}

void ProxyLogger::print()
{
    if (logger)
        logger->print();
}

void ProxyLogger::printTime()
{
    if (logger)
        logger->printTime();
}

void ProxyLogger::printLog(std::string output)
{
    if (logger)
        logger->printLog(output);
}

bool ProxyLogger::isActive()
{
    return logger;
}

std::string ProxyLogger::getInfo() const
{
    if (logger)
        return logger->getInfo();
    return "No logger";
}

void ProxyLogger::setInfo(const std::string &value)
{
    if (logger)
        logger->setInfo(value);
}

Time *ProxyLogger::getLocalTime() const
{
    if (logger)
        return logger->getLocalTime();
    return nullptr;
}

ProxyLogger::~ProxyLogger()
{
    if (logger)
        delete logger;
}
