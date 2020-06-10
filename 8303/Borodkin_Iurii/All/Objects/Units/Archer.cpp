#include "Archer.h"
#include <utility>

Archer::Archer(unsigned p, string name) : LongRange(std::move(name))
{
    player = p;
    attr = new Attributes(HpTypes::ARCHER, RngTypes::ARCHER, DmgTypes::ARCHER,
                          ArmTypes::ARCHER, ManaTypes::ARCHER);
}

Archer::Archer(Attributes* a, unsigned p)
{
    player = p;
    attr = a;
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

unsigned Archer::travelDistance() const
{
    return 1;
}

void Archer::heal(unsigned hp)
{
    if (attr->health + int(hp) < int(HpTypes::ARCHER))
        attr->health += hp;
    else
        attr->health = int(HpTypes::ARCHER);
}

void Archer::getDamage(unsigned damage)
{
    attr->health -= damage;
}

string Archer::type() const {return "Archer";}
