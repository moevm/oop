#ifndef LOGIC_LOGGER_FILE_HPP
#define LOGIC_LOGGER_FILE_HPP

#include "abstract_logger.hpp"

namespace l {
    class logger_file : public l::abstract_logger {
    private:
        std::string f_error;
        std::string f_warning;
        std::string f_debug;
        std::string f_message;
        std::string f_special;
        std::string f_all;

    public:
        logger_file ();

        void let (std::string& verbal, streams stream, bool decorated) override;
    };
}

#endif //LOGIC_LOGGER_FILE_HPP
