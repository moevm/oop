#ifndef GOGOLEV_STRATEGY_OUT_OF_BOUNDS_EXCEPTION_HPP
#define GOGOLEV_STRATEGY_OUT_OF_BOUNDS_EXCEPTION_HPP

#include "strategy_exception.hpp"

class outOfBoundsException : public strategyException {
public:
    explicit outOfBoundsException (const std::string& msg);
};


#endif //GOGOLEV_STRATEGY_OUT_OF_BOUNDS_EXCEPTION_HPP
