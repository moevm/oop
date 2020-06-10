#include "SpearMan.h"
#include <utility>

SpearMan::SpearMan(unsigned p, string name) : ShortRange(std::move(name)) {
    player = p;
    attr = new Attributes(HpTypes::SPEARMAN, RngTypes::SPEARMAN, DmgTypes::SPEARMAN,
                          ArmTypes::SPEARMAN, ManaTypes::SPEARMAN);
}

SpearMan::SpearMan(Attributes* a, unsigned p)
{
    player = p;
    attr = a;
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

unsigned SpearMan::travelDistance() const
{
    return 1;
}

void SpearMan::getDamage(unsigned damage)
{
    attr->health -= damage;
}

void SpearMan::heal(unsigned hp)
{
    if (attr->health + int(hp) < int(HpTypes::SPEARMAN))
        attr->health += hp;
    else
        attr->health = int(HpTypes::SPEARMAN);
}

string SpearMan::type() const {return "SpearMan";}
