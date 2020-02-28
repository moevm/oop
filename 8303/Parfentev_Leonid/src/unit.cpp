#include <random>

#include <assert.h>

#include "game.hpp"

std::default_random_engine
global_random {};

bool
BaseUnit::place()
{
    return _pos.map()->placeUnit(this);
}

void
BaseUnit::unplace()
{
    _pos.map()->removeUnit(this);
}

void
BaseUnit::die()
{
    unplace();
    delete this;
}

bool
BaseUnit::moveTo(const GamePos &pos)
{
    if (_pos)
        unplace();
    _pos = pos;
    return pos ? place() : true;
}

void
BaseUnit::takeDamage(int dmg)
{
    _health -= dmg;
}

int
Damage::evaluate() const
{
    return (int)round(spec.value
                      + std::uniform_real_distribution<>{
                          -spec.spread, spec.spread}(global_random));
}

void
BaseUnit::putDamage(BaseUnit *from,
                    DamageSpec modifier,
                    EventLoop *el)
{
    DamageSpec dmg = (from->baseDamage(position())
                      * damageMultipler(from)
                      * modifier);
    el->push_back(new Damage {dmg, this});
}



void
EventLoop::process()
{
    while (!_events.empty()) {
        Event *ev = _events.front();
        _events.pop();
        ev->execute(this);
        delete ev;
    }
}

void
Damage::execute(EventLoop *el)
{
    unit->takeDamage(evaluate());
    if (!unit->alive())
        el->push_back(new Death {unit});
}

void
Death::execute(EventLoop *)
{
    unit->die();
}
