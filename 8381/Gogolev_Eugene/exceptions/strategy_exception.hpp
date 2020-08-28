#ifndef GOGOLEV_STRATEGY_STRATEGY_EXCEPTION_HPP
#define GOGOLEV_STRATEGY_STRATEGY_EXCEPTION_HPP

#include "../stl.hpp"

class strategyException : public std::exception {
private:
    std::string info;
public:
    explicit strategyException (const std::string& msg);

    const char* what () const noexcept override;
};

#endif //GOGOLEV_STRATEGY_STRATEGY_EXCEPTION_HPP
