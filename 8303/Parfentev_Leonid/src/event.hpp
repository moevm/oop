#ifndef _EVENT_HPP_
#define _EVENT_HPP_

#include <queue>

#include "map.hpp"
#include "unit.hpp"


namespace events {

    class EventLoop;
    class Event {
    public:
        virtual void execute(EventLoop *) =0;

        virtual ~Event() {}
    };

    struct Damage : public Event {
        int dmg;
        BaseUnit *unit;

        Damage(int d, BaseUnit *u)
            :dmg{d}, unit{u} {}

        virtual void
        execute(EventLoop *) override;

        BaseUnit *target() const { return unit; }
    };

    struct Death : public Event {
        BaseUnit *unit;

        Death(BaseUnit *u) :unit{u} {}

        virtual void
        execute(EventLoop *) override;
    };



    class EventLoop {
        std::queue<Event *> _events {};

    public:
        void push_back(Event *e) { _events.push(e); }
        Event *front() const { return _events.front(); }
        bool empty() const { return _events.empty(); }
        void pop_front() { _events.pop(); }

        void process();

        virtual void handle(Damage *) {}
        virtual void handle(Death *) {}
    };

}

#endif
