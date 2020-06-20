#ifndef _H_EVENT_HPP
#define _H_EVENT_HPP

#include <set>

class Unit;
class EventListener;
class Event;

class EventEmitter {
    std::set<EventListener *> _listeners {};

public:
    void emit_shared(Event *e);
    void emit(Event *e);

    void subscribe(EventListener *l);
    void unsubscribe(EventListener *l);

    virtual ~EventEmitter() {}
};

class Event {
public:
    virtual ~Event() {}
};



class UnitEvent: public Event {
    Unit *_u;

public:
    UnitEvent(Unit *u) :_u{u} {}

    Unit *unit() const { return _u; }
};

class UnitDeathEvent: public UnitEvent {
public:
    using UnitEvent::UnitEvent;
};

class UnitAddedEvent: public UnitEvent {
public:
    using UnitEvent::UnitEvent;
};

class UnitLiveDeletedEvent: public UnitEvent {
public:
    using UnitEvent::UnitEvent;
};

class UnitTakesDamageEvent: public Event {
    Unit *_u;
    int _dmg;

public:
    UnitTakesDamageEvent(Unit *u, int dmg)
        :_u{u}, _dmg{dmg} {}

    Unit *unit() const { return _u; }
    int damage() const { return _dmg; }
};

class UnitGetsHealedEvent: public Event {
    Unit *_u;
    int _hp;

public:
    UnitGetsHealedEvent(Unit *u, int hp)
        :_u{u}, _hp{hp} {}

    Unit *unit() const { return _u; }
    int health() const { return _hp; }
};

class AttackEvent: public Event {
    Unit *_a, *_b;

public:
    AttackEvent(Unit *a, Unit *b) :_a{a}, _b{b} {}

    Unit *attacker() const { return _a; }
    Unit *target() const { return _b; }
};

class UnitWasAttackedEvent: public AttackEvent {
public:
    using AttackEvent::AttackEvent;
};

class UnitAttackedEvent: public AttackEvent {
public:
    using AttackEvent::AttackEvent;
};



class EventListener {
public:
    virtual void handle(Event *e) =0;

    virtual ~EventListener() {}
};

class EventForwarder: public EventEmitter,
                      public EventListener {
public:
    virtual void
    handle(Event *e) override
    {
        emit_shared(e);
    }
};

#endif
