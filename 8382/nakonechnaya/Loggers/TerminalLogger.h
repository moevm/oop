#ifndef OOP_TERMINALLOGGER_H
#define OOP_TERMINALLOGGER_H
#include "Logger.h"

class TerminalLogger : public Logger{
public:
    TerminalLogger() : count(0) {};
    void print() final;
    void setLog(std::string logString) final {this->log = logString;};
    void addLog(std::string logString) final {log += logString;};
    void setFormat(int format) final {this->format = format;};
    int getFormat() final { return format;};
    friend std::ostream& operator<< (std::ostream &out, const TerminalLogger &logger);
private:
    std::string log;
    int count;
    int format;
};
#endif //OOP_TERMINALLOGGER_H
