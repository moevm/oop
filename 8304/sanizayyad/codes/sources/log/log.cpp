
#include "log.hpp"

std::string Log::getCurrentTime() const
{
    auto currentTime = time(nullptr);

    return asctime(localtime(&currentTime));
}

std::string Log::getMessageType(TYPE type) const
{
    auto time = getCurrentTime();
    time.pop_back();

    if (type == TYPE::DBG) {
        return "DEBUG(" + time + "): ";
    }
    else if (type == TYPE::INFO) {
        return "INFO(" + time + "): ";
    }
    else if (type == TYPE::ERR) {
        return "ERROR(" + time + "): ";
    }

    return "WARNING(" + time + "): ";
}



