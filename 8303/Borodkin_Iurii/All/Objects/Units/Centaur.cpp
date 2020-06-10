#include "Centaur.h"
#include <utility>

Centaur::Centaur(unsigned p, string name) : Rider(std::move(name))
{
    player = p;
    attr = new Attributes(HpTypes::CENTAUR, RngTypes::CENTAUR, DmgTypes::CENTAUR,
                          ArmTypes::CENTAUR, ManaTypes::CENTAUR);
}

Centaur::Centaur(Attributes* a, unsigned p)
{
    player = p;
    attr = a;
}

Centaur::Centaur(const Centaur& unit) : Rider(unit)
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

unsigned Centaur::travelDistance() const
{
    return 3;
}

void Centaur::heal(unsigned hp)
{
    if (attr->health + int(hp) < int(HpTypes::CENTAUR))
        attr->health += hp;
    else
        attr->health = int(HpTypes::CENTAUR);
}

void Centaur::getDamage(unsigned damage)
{
    attr->health -= damage;
}

string Centaur::type() const {return "Centaur";}
