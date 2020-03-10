#include "SwordsMan.h"
#include <utility>

SwordsMan::SwordsMan(std::string name) : ShortRange(std::move(name))
{
    attr = new Attributes(HpTypes::SWORDSMAN, RngTypes::SWORDSMAN, DmgTypes::SWORDSMAN,
                          ArmTypes::SWORDSMAN, ManaTypes::SWORDSMAN);
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

std::string SwordsMan::type() const {return "SwordsMan";}
