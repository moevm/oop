
#ifndef LOGIC_Timer_HPP
#define LOGIC_Timer_HPP

#include <thread>
namespace utils
{
class Timer
{
    bool clear = false;

public:
    template <typename Function>
    void setTimeout(Function function, int delay);

    template <typename Function>
    void setInterval(Function function, int interval);

    void stop();
};
} 
#endif 
