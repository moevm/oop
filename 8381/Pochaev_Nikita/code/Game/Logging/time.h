#ifndef TIME_H
#define TIME_H

#include <iostream>
#include <string>
#include <ctime>    // localtime
#include <iomanip>  // put_time
#include <sstream>  // stringstream
#include <chrono>   // chrono::system_clock

using TimePoint = std::chrono::time_point<std::chrono::system_clock>;
using CurrentTime =  std::time_t;

class Time
{
public:
    Time();
    void update();
    std::string getProgWorkTime();
    friend std::ostream& operator<< (std::ostream &out, const Time &time);

private:
    TimePoint progStartTimePoint;
    TimePoint currentTimePoint{};
    CurrentTime currTime{};
};

#endif // TIME_H
