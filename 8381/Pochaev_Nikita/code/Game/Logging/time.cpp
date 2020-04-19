#include "time.h"

Time::Time()
{
    progStartTimePoint = std::chrono::system_clock::now();
}

void Time::update()
{
    currentTimePoint = std::chrono::system_clock::now();
    currTime = std::chrono::system_clock::to_time_t(currentTimePoint);
}

std::string Time::getProgWorkTime()
{
    update();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(currentTimePoint - progStartTimePoint);

    return "Program was working for " + std::to_string(duration.count()) + "seconds\n";
}

std::ostream& operator<< (std::ostream &out, Time &time)
{
    time.update();
    out << std::put_time(std::localtime(&time.currTime), "%F %T");

    return out;
}
