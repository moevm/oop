#include "Panzer.h"
#include <utility>

Panzer::Panzer(unsigned p, string name) : Rider(std::move(name))
{
    player = p;
    attr = new Attributes(HpTypes::PANZER, RngTypes::PANZER, DmgTypes::PANZER,
                          ArmTypes::PANZER, ManaTypes::PANZER);
}

Panzer::Panzer(Attributes* a, unsigned p)
{
    player = p;
    attr = a;
}

Panzer::Panzer(const Panzer& unit) : Rider(unit)
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

unsigned Panzer::travelDistance() const
{
    return 2;
}

void Panzer::getDamage(unsigned damage)
{
    attr->health -= damage;
}

void Panzer::heal(unsigned hp)
{
    if (attr->health + int(hp) < int(HpTypes::PANZER))
        attr->health += hp;
    else
        attr->health = int(HpTypes::PANZER);
}

string Panzer::type() const {return "Panzer";}
