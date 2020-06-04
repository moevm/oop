#include "abstract_logger.hpp"

l::abstract_logger::abstract_logger() {
    this->enabled = true;
}



std::string& l::abstract_logger::get_time_name (bool full) {
    time_t raw_time;
    struct tm* time_info;
    char buffer[80];

    time(&raw_time);
    time_info = localtime(&raw_time);

    const char* format;
    if (full) format = "%d-%m-%Y %H:%M:%S";
    else format = "%d-%m-%Y";

    strftime(buffer, sizeof(buffer), format, time_info);
    auto now = new std::string(buffer);
    return *now;
}

bool l::abstract_logger::is_enabled() const {
    return enabled;
}

void l::abstract_logger::set_enabled(bool en) {
    abstract_logger::enabled = en;
}
