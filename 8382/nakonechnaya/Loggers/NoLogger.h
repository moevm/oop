#ifndef OOP_NOLOGGER_H
#define OOP_NOLOGGER_H
#include "Logger.h"

class NoLogger : public Logger{
public:
    void setLog(std::string log) final {};
    void print() final {};
    void addLog(std::string logString) final {};
    void setFormat(int format) final {};
    int getFormat() final { return 0;};
};
#endif //OOP_NOLOGGER_H
