#ifndef LOGIC_ABSTRACT_LOGGER_HPP
#define LOGIC_ABSTRACT_LOGGER_HPP

#include "../base/third_party_includes.hpp"

namespace l {
    enum loggers {
        server_console_logger = 0, broadcast_logger = 1, server_file_logger = 2, user_logger = 3
    };

    enum streams : char {
        error = 'E', warning = 'W', debug = 'D', message = 'M', special = 'S'
    };



    class abstract_logger {
    public:
        abstract_logger ();

        static std::string& get_time_name (bool full);
        virtual void let (std::string& verbal, streams stream, bool decorated) = 0;

        bool is_enabled() const;
        void set_enabled(bool enabled);

        virtual ~abstract_logger () = default;

    private:
        bool enabled;
    };
}


#endif //LOGIC_ABSTRACT_LOGGER_HPP
