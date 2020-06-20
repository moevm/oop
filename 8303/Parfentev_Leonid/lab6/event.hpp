#ifndef _H_EVENT_HPP
#define _H_EVENT_HPP

#include <set>

class EventListener;
class Event;

class EventEmitter {
    std::set<EventListener *> _listeners {};

public:
    void emit_shared(Event *e) const;
    void emit(Event *e) const;

    void subscribe(EventListener *l);
    void unsubscribe(EventListener *l);

    virtual ~EventEmitter() {}
};

class Event {
public:
    virtual ~Event() {}
};

class EventListener {
public:
    virtual void handle(Event *e) =0;

    virtual ~EventListener() {}
};

class EventForwarder;

namespace events {

    class Forwarded: public Event {
        Event *_e;
        EventForwarder *_f;

    public:
        Forwarded(Event *e, EventForwarder *f)
            :_e{e}, _f{f} {}

        Event *event() const { return _e; }
        EventForwarder *forwarder() const { return _f; }
    };

}

class EventForwarder: public EventEmitter,
                      public EventListener {
public:
    virtual void
    handle(Event *e) override
    {
        emit(new events::Forwarded {e, this});
    }
};

#endif
