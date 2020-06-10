#ifndef LOGGERTERMINAL_H
#define LOGGERTERMINAL_H
#include "Logger.h"
#include <QTextBrowser>

class LoggerTerminal : public ILogger
{
public:
    LoggerTerminal(QTextBrowser*);
    ILogger& operator<<(const std::string&) override;
private:
    QTextBrowser* terminal;
};

#endif // LOGGERTERMINAL_H
