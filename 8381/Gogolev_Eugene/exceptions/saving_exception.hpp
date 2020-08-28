#ifndef GOGOLEV_STRATEGY_SAVING_EXCEPTION_HPP
#define GOGOLEV_STRATEGY_SAVING_EXCEPTION_HPP

#include "strategy_exception.hpp"

class savingException : public strategyException {
public:
    explicit savingException (const std::string& msg);
};


#endif //GOGOLEV_STRATEGY_SAVING_EXCEPTION_HPP
