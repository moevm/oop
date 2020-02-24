#include <random>

#include <assert.h>

#include "game.hpp"

std::default_random_engine
BaseUnit::random {};

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
    if (!alive())
        die();
}

int
BaseUnit::getDamageValue(Damage damage)
{
    return (int)round(damage.value
                      + std::uniform_real_distribution<>{
                          -damage.spread, damage.spread}(random));
}

void
BaseUnit::beAttacked(const BaseUnit *by, Damage modifier)
{
    takeDamage(getDamageValue(
                   by->baseDamage(position())
                   * damageMultipler(by)
                   * modifier));
}
