#include "ArmorPack.h"

ArmorPack::ArmorPack()
{
}

Attributes ArmorPack::buff()
{
    return Attributes(0, 0, 0, 100, 0);
}

std::string ArmorPack::type() {return "Armor";}

void ArmorStrategy::buff(Object *unit, Pack** pack)
{
    if (!(unit->type() == "Archer" || unit->type() == "Wizard"))
    {
        *unit += **pack;
        delete *pack;
        *pack = nullptr;
    }
}
