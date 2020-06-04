#include "logger_file.hpp"

#include "../filesys/file_gate.hpp"



l::logger_file::logger_file() : l::abstract_logger() {
    f_error = "_error.log";
    f_warning = "_warning.log";
    f_debug = "_debug.log";
    f_message = "_message.log";
    f_special = "_special.log";
    f_all = "_all.log";
}

void l::logger_file::let (std::string& verbal, streams stream, bool decorated) {
    std::string this_file_name = get_time_name(false);
    std::string all_file_name = this_file_name + f_all;

    switch (stream) {
        case error:
            this_file_name += f_error;
            break;
        case warning:
            this_file_name += f_warning;
            break;
        case debug:
            this_file_name += f_debug;
            break;
        case message:
            this_file_name += f_message;
            break;
        case special:
            this_file_name += f_special;
            break;
    }

    std::string out;
    if (decorated) {
        std::stringstream ss;
        ss << (char) stream << "! " << abstract_logger::get_time_name(true) << ": " << verbal << "\n";
        out = ss.str();
    } else {
        out = verbal += "\n";
    }

    file::file_gate::pass(this_file_name, out, file::append, file::logs);
    file::file_gate::pass(all_file_name, out, file::append, file::logs);
}
