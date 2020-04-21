#include "time.h"

Time::Time()
{
    progStartTimePoint = std::chrono::system_clock::now();
    currTime = std::chrono::system_clock::to_time_t(progStartTimePoint);
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

    return std::to_string(duration.count());
}

std::ostream& operator<< (std::ostream &out, const Time &time)
{
    struct std::tm ptm = *std::localtime(&time.currTime);
    out << std::put_time(&ptm, "%Y-%m-%d %H:%M:%S");
    return out;
}
