#ifndef LOGIC_LOGGER_USER_HPP
#define LOGIC_LOGGER_USER_HPP

#include "abstract_logger.hpp"

namespace l {
    class logger_user : public l::abstract_logger {
    public:
        void let (std::string& verbal, streams stream, bool decorated) override;
    };
}

#endif //LOGIC_LOGGER_USER_HPP
