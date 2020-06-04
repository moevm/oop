#ifndef LOGIC_LOG_HPP
#define LOGIC_LOG_HPP

#include "../base/third_party_includes.hpp"
#include "../base/interfaces.hpp"
#include "../utils/singleton.hpp"

#include "abstract_logger.hpp"
#include "logger_server.hpp"
#include "logger_broadcast.hpp"
#include "logger_user.hpp"
#include "logger_file.hpp"

namespace l {
    class on : public utils::singleton<on> {
        friend class utils::singleton<on>;
    private:
        void send (bool decorated);

        abstract_logger** logs;
        streams stream;
        std::ostringstream alpha;

        using utils::singleton<on>::get;

    protected:
        on ();

    public:
        ~on ();

        static void enable_logger (bool enabled, loggers logger);
        static void enable_all (bool enabled);

        static on& say (streams str = message);
        template<typename T>
        static void say (const T& value, streams str = message);
        static void say (json& object, streams str = message);

        template<typename T>
        friend l::on& operator<< (l::on& out, const T& value);
        friend l::on& operator<< (l::on& out, json& object);
        friend l::on& operator<< (l::on& out, l::on& (* f) (l::on&));
        friend void operator<< (l::on& out, void (* f) (l::on&));

        static on& over (on& out);
        static void out (on& out);
        //....
    };


    template<typename T>
    l::on& operator<< (l::on &out, const T &value) {
        out.alpha << value;
        return out;
    }

    template<typename T>
    void l::on::say (const T &value, l::streams str) {
        on& fin = utils::singleton<on>::get();
        fin.stream = str;
        fin.alpha << value;
        fin.send(true);
    }
}


#endif //LOGIC_LOG_HPP
