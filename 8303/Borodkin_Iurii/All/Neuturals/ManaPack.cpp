#include "ManaPack.h"

ManaPack::ManaPack()
{
}

Attributes ManaPack::buff()
{
    return Attributes(0, 0, 0, 0, 100);
}

std::string ManaPack::type() {return "Mana";}

void ManaStrategy::buff(Object *unit, Pack** pack)
{
    if (unit->type() == "Archer" || unit->type() == "Wizard")
    {
        *unit += **pack;
        delete *pack;
        *pack = nullptr;
    }
}
