#include "Centaur.h"
#include <utility>

Centaur::Centaur(std::string name) : Rider(std::move(name))
{
    attr = new Attributes(HpTypes::CENTAUR, RngTypes::CENTAUR, DmgTypes::CENTAUR,
                          ArmTypes::CENTAUR, ManaTypes::CENTAUR);
}

Centaur::Centaur(const Centaur& unit)
{
    _name = unit._name;
    attr = new Attributes(unit.health(), unit.range(), unit.damage(),
                          unit.armor(), unit.mana());
}

Centaur::Centaur(Centaur&& unit)
{
    _name = std::move(unit.name());
    attr = unit.attr;
    unit.attr = nullptr;
}

std::string Centaur::type() const {return "Centaur";}
