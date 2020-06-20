#include <iostream>
#include <limits>

#include <ctype.h>

#include "map.hpp"
#include "event.hpp"
#include "interactive.hpp"

namespace interactive {

    void
    Session::skip_to_eol(std::istream &is)
    {
        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    void
    Session::spin(std::istream &is, std::ostream &os)
    {
        is >> std::ws;
        char c = is.get();
        if (c == '#') {
            skip_to_eol(is);
            return;
        }
        is.putback(c);

        is.clear();
        std::string cmd_name;
        is >> cmd_name;
        if (is.eof())
            return;

        const CommandFactory *factory =
            findCommandFactory(cmd_name);
        if (!factory) {
            os << "Unknown command: `" << cmd_name << "'" << std::endl;
            skip_to_eol(is);
            return;
        }

        Command *cmd = factory->create(is, os);
        if (!cmd) {
            skip_to_eol(is);
            return;
        }

        char next;
        do
            next = is.get();
        while (isblank(next));
        if (next != '\n') {
            os << "Extra characters after command" << std::endl;
            skip_to_eol(is);
            delete cmd;
            return;
        }

        cmd->run(this, os);
        delete cmd;
    }

    void
    Session::run(std::istream &is, std::ostream &os)
    {
        while (!_stop_running
               && !is.eof())
            spin(is, os);
    }

    SimpleCommandFactory<QuitCommand>
    BasicSession::quit_factory {};

}
