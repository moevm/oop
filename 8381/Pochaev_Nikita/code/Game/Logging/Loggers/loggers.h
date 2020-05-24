#ifndef LOGGERS_H
#define LOGGERS_H

// I wanted to use filesystem... But MiniGW 8.1 (for C++17-20) doesn't work correctly
#include <QDir>
#include <QString>

#include "../ILogger.h"
#include "../time.h"
// ha-ha absolute path without CLion refactoriing
#include "../../../AuxiliaryFunctionality/TextColoring.h"

class TerminalLogger : public ILogger
{
public:
    ~TerminalLogger() override;
    TerminalLogger();
    eLOGGER_TYPE getType() override;

    bool isActive() override;
    void printLog(std::string outInf) override;
    void print() override;
    void printCurrTime() override;
    void printProgWorkingTime() override;

    friend std::ostream& operator<< (std::ostream &out, ILogger &log);
    std::shared_ptr<Time>& getTime() override;
    std::string getLogInf() const override;

private:
    std::shared_ptr<Time> time;
    std::string logInf{};
};

class FileLogger : public ILogger
{
public:
    ~FileLogger() override;
    FileLogger();
    eLOGGER_TYPE getType() override;

    bool isActive() override;
    void printLog(std::string outInf) override;
    void print() override;
    void printCurrTime() override;
    void printProgWorkingTime() override;

    friend std::ostream& operator<< (std::ostream &out, ILogger &log);
    std::shared_ptr<Time>& getTime() override;
    std::string getLogInf() const override;

private:
    std::shared_ptr<Time> time;
    std::string logInf{};
    std::ofstream fout;
};

class ProxyLogger : public ILogger
{
public:
    ~ProxyLogger() override = default;
    ProxyLogger(eLOGGER_TYPE loggerType);
    eLOGGER_TYPE getType() override;

    bool isActive() override;
    void printLog(std::string outInf) override;
    void print() override;
    void printCurrTime() override;
    void printProgWorkingTime() override;

    std::shared_ptr<Time>& getTime() override;
    std::string getLogInf() const override;

private:
    std::shared_ptr<ILogger> logger;
};

#endif // LOGGERS_H
