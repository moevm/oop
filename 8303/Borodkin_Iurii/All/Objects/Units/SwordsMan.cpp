#include "SwordsMan.h"
#include <utility>

SwordsMan::SwordsMan(unsigned p, string name) : ShortRange(std::move(name))
{
    player = p;
    attr = new Attributes(HpTypes::SWORDSMAN, RngTypes::SWORDSMAN, DmgTypes::SWORDSMAN,
                          ArmTypes::SWORDSMAN, ManaTypes::SWORDSMAN);
}

SwordsMan::SwordsMan(Attributes* a, unsigned p)
{
    player = p;
    attr = a;
}

SwordsMan::SwordsMan(const SwordsMan& unit) : ShortRange(unit)
{
    _name = unit._name;
    attr = new Attributes(unit.health(), unit.range(), unit.damage(),
                          unit.armor(), unit.mana());
}

SwordsMan::SwordsMan(SwordsMan&& unit)
{
    _name = std::move(unit.name());
    attr = unit.attr;
    unit.attr = nullptr;
}

unsigned SwordsMan::travelDistance() const
{
    return 1;
}

void SwordsMan::getDamage(unsigned damage)
{
    attr->health -= damage;
}

void SwordsMan::heal(unsigned hp)
{
    if (attr->health + int(hp) < int(HpTypes::SWORDSMAN))
        attr->health += hp;
    else
        attr->health = int(HpTypes::SWORDSMAN);
}

string SwordsMan::type() const { return "SwordsMan"; }
