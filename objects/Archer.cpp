#include "Archer.h"
#include <utility>

Archer::Archer(std::string name) : LongRange(std::move(name)) {
    attr = new Attributes(HpTypes::ARCHER, RngTypes::ARCHER, DmgTypes::ARCHER,
                          ArmTypes::ARCHER, ManaTypes::ARCHER);
}

Archer::Archer(const Archer& unit) : LongRange(unit)
{
    _name = unit._name;
    attr = new Attributes(unit.health(), unit.range(), unit.damage(),
                          unit.armor(), unit.mana());
}

Archer::Archer(Archer&& unit)
{
    _name = std::move(unit.name());
    attr = unit.attr;
    unit.attr = nullptr;
}

std::string Archer::type() const {return "Archer";}
