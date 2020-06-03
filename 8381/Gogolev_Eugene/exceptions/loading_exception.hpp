#ifndef GOGOLEV_STRATEGY_LOADING_EXCEPTION_HPP
#define GOGOLEV_STRATEGY_LOADING_EXCEPTION_HPP

#include "strategy_exception.hpp"

class loadingException : public strategyException {
public:
    explicit loadingException (const std::string& msg);
};


#endif //GOGOLEV_STRATEGY_LOADING_EXCEPTION_HPP
