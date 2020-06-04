#ifndef LOGIC_LOGGER_BROADCAST_HPP
#define LOGIC_LOGGER_BROADCAST_HPP

#include "abstract_logger.hpp"

namespace l {
    class logger_broadcast : public l::abstract_logger {
    public:
        void let (std::string& verbal, streams stream, bool decorated) override;
    };
}

#endif //LOGIC_LOGGER_BROADCAST_HPP
