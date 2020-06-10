#include "LoggerTerminal.h"

LoggerTerminal::LoggerTerminal(QTextBrowser* t) : terminal(t)
{}

ILogger& LoggerTerminal::operator<<(const std::string& str)
{
    terminal->append(str.c_str());
    return *this;
}
