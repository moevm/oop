#include "logger.h"

#include <sstream>


Logger& Logger::operator<<(const std::string &str){
    buffer << str;
    return *this;
}


bool Logger::empty() const{
    return buffer.str().empty();
}


std::ostream& operator<<(std::ostream& os, Logger& logger){
    os << logger.buffer.str();
    logger.buffer.str(std::string());
    return os;
}
