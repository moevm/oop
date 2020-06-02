#ifndef LAB2_OOP_TIMEFORMAT_H
#define LAB2_OOP_TIMEFORMAT_H

#include <ctime>
#include "LogFormat.h"

class TimeFormat: public LogFormat {
  std::string getFormatted(std::string &stringToFormat) override {
    time_t rawtime;
    struct tm *timeInfo;
    char buffer[80];                                // строка, в которой будет храниться текущее время

    time (&rawtime);                               // текущая дата в секундах
    timeInfo = localtime (&rawtime);               // текущее локальное время, представленное в структуре

    strftime (buffer, 80, " [%c] ", timeInfo); // форматируем строку времени

    return buffer + stringToFormat;
  }
};

#endif //LAB2_OOP_TIMEFORMAT_H
