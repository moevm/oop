#ifndef _H_EVENT_TYPES_HPP
#define _H_EVENT_TYPES_HPP

#include "point.hpp"
#include "event.hpp"


class Unit;
class Base;
class NeutralObject;
class Player;


class UnitEvent: public Event {
    Unit *_u;

public:
    UnitEvent(Unit *u) :_u{u} {}

    Unit *unit() const { return _u; }
};

class AttackEvent: public Event {
    Unit *_a, *_b;

public:
    AttackEvent(Unit *a, Unit *b) :_a{a}, _b{b} {}

    Unit *attacker() const { return _a; }
    Unit *target() const { return _b; }
};

class BaseEvent: public Event {
    Base *_b;

public:
    BaseEvent(Base *b) :_b{b} {}

    Base *base() const { return _b; }
};

class PlayerEvent: public Event {
    Player *_p;

public:
    PlayerEvent(Player *p) :_p{p} {}

    Player *player() const { return _p; }
};

class UnitMoveEvent: public UnitEvent {
    Vec2 _src;

public:
    UnitMoveEvent(Unit *u, Vec2 src)
        :UnitEvent{u}, _src{src} {}

    Vec2 sourcePos() const { return _src; }
};



namespace events {

    class UnitDeath: public UnitEvent {
    public:
        using UnitEvent::UnitEvent;
    };

    class UnitAdded: public UnitEvent {
    public:
        using UnitEvent::UnitEvent;
    };

    class UnitLiveDeleted: public UnitEvent {
    public:
        using UnitEvent::UnitEvent;
    };

    class UnitTakesDamage: public UnitEvent {
        int _dmg;

    public:
        UnitTakesDamage(Unit *u, int dmg)
            :UnitEvent{u}, _dmg{dmg} {}

        int damage() const { return _dmg; }
    };

    class UnitGetsHealed: public UnitEvent {
        int _hp;

    public:
        UnitGetsHealed(Unit *u, int hp)
            :UnitEvent{u}, _hp{hp} {}

        int health() const { return _hp; }
    };

    class UnitWasAttacked: public AttackEvent {
    public:
        using AttackEvent::AttackEvent;
    };

    class UnitAttacked: public AttackEvent {
        Vec2 _tc;

    public:
        UnitAttacked(Unit *u, Vec2 tc, Unit *tu)
            :AttackEvent{u, tu}, _tc{tc} {}

        Vec2 targetCoordinates() const { return _tc; }
    };

    class UnitMoved: public UnitMoveEvent {
    public:
        using UnitMoveEvent::UnitMoveEvent;
    };

    class UnitTeleported: public UnitMoveEvent {
    public:
        using UnitMoveEvent::UnitMoveEvent;
    };

    class UnitUsedObject: public UnitEvent {
        NeutralObject *_n;

    public:
        UnitUsedObject(Unit *u, NeutralObject *n)
            :UnitEvent{u}, _n{n} {}

        NeutralObject *neutralObject() const { return _n; }
    };



    class BaseDestroyed: public BaseEvent {
    public:
        using BaseEvent::BaseEvent;
    };



    class TurnStarted: public PlayerEvent {
    public:
        using PlayerEvent::PlayerEvent;
    };

    class TurnOver: public PlayerEvent {
    public:
        using PlayerEvent::PlayerEvent;
    };

}

#endif
