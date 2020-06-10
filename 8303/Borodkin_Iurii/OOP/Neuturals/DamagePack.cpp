#include "DamagePack.h"

DamagePack::DamagePack()
{
}

Attributes DamagePack::buff()
{
    return Attributes(0, 0, 100, 0, 0);
}

std::string DamagePack::type() {return "Damage";}

void DamageStrategy::buff(Object *unit, Pack** pack)
{
    *unit += **pack;
    delete *pack;
    *pack = nullptr;
}
