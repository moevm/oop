#include "strategy_exception.hpp"

const char *strategyException::what() const noexcept {
    return info.c_str();
}

strategyException::strategyException(const std::string &msg) {
    this->info = "[S]" + msg;
}
