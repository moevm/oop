#include <random>

#include <assert.h>

#include "map.hpp"
#include "event.hpp"
#include "unit.hpp"


std::default_random_engine
global_random {};

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
BaseUnit::putDamage(MapIter from,
                    DamageSpec modifier,
                    events::EventLoop *el)
{
    MapIter iter = from.otherAt(point());
    DamageSpec dmg = (from->unit()->baseDamage(iter)
                      * damageMultipler(from)
                      * modifier);
    el->push(new events::Damage {dmg.evaluate(), iter});
}
