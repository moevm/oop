#include <random>

#include <assert.h>

#include "map.hpp"
#include "event.hpp"
#include "unit.hpp"


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
BaseUnit::DamageSpec::evaluate() const
{
    return (int)round(value
                      + std::uniform_real_distribution<>{
                          -spread, spread}(global_random));
}

void
BaseUnit::putDamage(BaseUnit *from,
                    DamageSpec modifier,
                    events::EventLoop *el)
{
    DamageSpec dmg = (from->baseDamage(position())
                      * damageMultipler(from)
                      * modifier);
    el->push(new events::Damage {dmg.evaluate(), this});
}
