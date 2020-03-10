#include "SpearMan.h"
#include <utility>

SpearMan::SpearMan(std::string name) : ShortRange(std::move(name)) {
    attr = new Attributes(HpTypes::SPEARMAN, RngTypes::SPEARMAN, DmgTypes::SPEARMAN,
                          ArmTypes::SPEARMAN, ManaTypes::SPEARMAN);
}

SpearMan::SpearMan(const SpearMan& unit) : ShortRange(unit)
{
    _name = unit._name;
    attr = new Attributes(unit.health(), unit.range(), unit.damage(),
                          unit.armor(), unit.mana());
}

SpearMan::SpearMan(SpearMan&& unit)
{
    _name = std::move(unit.name());
    attr = unit.attr;
    unit.attr = nullptr;
}

std::string SpearMan::type() const {return "SpearMan";}
