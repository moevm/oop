#ifndef RANDINT_H
#define RANDINT_H

#include <random>
#include <cassert>

class RandInt{
    static std::random_device device;
    std::mt19937 engine;

public:
    RandInt(const RandInt&) = delete;
    RandInt(RandInt&&) = delete;
    RandInt& operator=(const RandInt&) = delete;

    RandInt()
    {
        engine.seed(device());
    }

    int operator()(int min, int max){
        assert(min < max);
        std::uniform_int_distribution dist(min, max);
        return dist(engine);
    }
};


#endif // RANDINT_H
