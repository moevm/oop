#include "HealthPack.h"

HealthPack::HealthPack()
{
}

Attributes HealthPack::buff()
{
    return Attributes(100, 0, 0, 0, 0);
}

std::string HealthPack::type() {return "Health";}

void HealthStrategy::buff(Object *unit, Pack** pack)
{
    *unit += **pack;
    delete *pack;
    *pack = nullptr;
}
