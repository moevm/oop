#ifndef PRINTER_H
#define PRINTER_H

#include <fstream>

class Logger;

class Printer
{
    inline static float timer_s = 0;

    Logger &logger;
    std::ostream &os;
    bool file;

public:
    static void init();

    Printer(Logger& logger);
    Printer(Logger& logger, std::ofstream& ofs);
    ~Printer();

    void update(float time_ms);
    void print();
};

#endif // PRINTER_H
