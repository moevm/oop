#ifndef _H_LOGGING_HPP
#define _H_LOGGING_HPP

#include <string>
#include <utility>

#include "event.hpp"
#include "event_printer.hpp"


namespace events {

    class UserActionEvent: public Event {
        Player *_p;
        std::string _s;

    public:
        UserActionEvent(Player *p, std::string s)
            :_p{p}, _s{std::move(s)} {}

        const std::string &
        message() const { return _s; }

        Player *player() const { return _p;}
    };

}

class LoggingEventPrinter: public EventPrinter {
public:
    using EventPrinter::EventPrinter;

    virtual void
    handle(Event *e) override
    {
        if (auto *ee = dynamic_cast<events::UserActionEvent *>(e)) {
            ostream() << ee->player()->name()
                      << ": " << ee->message() << "\n";
            return;
        }

        EventPrinter::handle(e);
    }
};

#endif
