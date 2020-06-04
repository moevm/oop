#ifndef LOGIC_TIMER_HPP
#define LOGIC_TIMER_HPP

#include <thread>

namespace utils {
    class timer {
        bool clear = false;

    public:
        template<typename Function>
        void setTimeout(Function function, int delay);

        template<typename Function>
        void setInterval(Function function, int interval);

        void stop();
    };

    template<typename Function>
    void timer::setTimeout(Function function, int delay) {
        this->clear = false;
        std::thread t([=]() { // Idk how it works but it works TODO
            if(this->clear) return;
            std::this_thread::sleep_for(std::chrono::milliseconds(delay));
            if(this->clear) return;
            function();
        });
        t.detach();
    }

    template<typename Function>
    void timer::setInterval(Function function, int interval) {
        this->clear = false;
        std::thread t([=]() {
            while(true) {
                if(this->clear) return;
                std::this_thread::sleep_for(std::chrono::milliseconds(interval));
                if(this->clear) return;
                function();
            }
        });
        t.detach();
    }

    void timer::stop() {
        this->clear = true;
    }
}

#endif //LOGIC_TIMER_HPP
