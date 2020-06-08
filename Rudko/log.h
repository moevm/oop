#ifndef LOG_H
#define LOG_H

#include "gfield.h"
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

class log
{
private:
    std::ofstream file;
    GField* field;
public:
    log();
    log(int);
    ~log();
    void logf(std::string, int, int, int , std::string);
    void logt(std::string, int, int, int , std::string);
};

#endif // LOG_H
