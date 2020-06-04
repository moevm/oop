#include "logger_server.hpp"

#define ERROR 31
#define SPECIAL 32
#define WARNING 33
#define DEBUG 96
#define MESSAGE 38



void l::logger_server::print_color(std::string &verbal, int color) { // TODO addind terminal type check maybe?..
    std::cout << "\033[" << color << "m" << verbal << "\033[m" << std::endl;
}

void l::logger_server::let(std::string &verbal, streams stream, bool decorated) {
    if (decorated) {
        std::stringstream ss;
        ss << (char) stream << "! " << abstract_logger::get_time_name(true) << ": " << verbal;
        std::string timed_verbal = ss.str();
        switch (stream) {
            case error:
                print_color(timed_verbal, ERROR);
                break;
            case warning:
                print_color(timed_verbal, WARNING);
                break;
            case debug:
                print_color(timed_verbal, DEBUG);
                break;
            case message:
                print_color(timed_verbal, MESSAGE);
                break;
            case special:
                print_color(timed_verbal, SPECIAL);
                break;
        }
    } else {
        std::cout << verbal << std::endl;
    }
}
