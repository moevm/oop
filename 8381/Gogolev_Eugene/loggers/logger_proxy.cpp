#include "logger_proxy.hpp"

LoggerProxy::LoggerProxy (Logger* concrete) {
    child = concrete;
}

void LoggerProxy::setChild (Logger* concrete) {
    delete child;
    child = concrete;
}

void LoggerProxy::log (const string& message) {
    if (child) child->log(message);
}



