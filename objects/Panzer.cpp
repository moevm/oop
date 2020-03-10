#include "Panzer.h"
#include <utility>

Panzer::Panzer(std::string name) : Rider(std::move(name))
{
    attr = new Attributes(HpTypes::PANZER, RngTypes::PANZER, DmgTypes::PANZER,
                          ArmTypes::PANZER, ManaTypes::PANZER);
}

Panzer::Panzer(const Panzer& unit)
{
    _name = unit._name;
    attr = new Attributes(unit.health(), unit.range(), unit.damage(),
                          unit.armor(), unit.mana());
}

Panzer::Panzer(Panzer&& unit)
{
    _name = std::move(unit.name());
    attr = unit.attr;
    unit.attr = nullptr;
}

std::string Panzer::type() const {return "Panzer";}
