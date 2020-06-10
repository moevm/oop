#include "Wizard.h"
#include <utility>
#include <QDebug>

Wizard::Wizard(unsigned p, string name) : LongRange(std::move(name)) {
        player = p;
    attr = new Attributes(HpTypes::WIZARD, RngTypes::WIZARD, DmgTypes::WIZARD,
                          ArmTypes::WIZARD, ManaTypes::WIZARD);
}

Wizard::Wizard(Attributes* a, unsigned p)
{
    player = p;
    attr = a;
}

Wizard::Wizard(const Wizard& unit) : LongRange(unit)
{
    _name = unit._name;
    attr = new Attributes(unit.health(), unit.range(), unit.damage(),
                          unit.armor(), unit.mana());
}

Wizard::Wizard(Wizard&& unit)
{
    _name = std::move(unit.name());
    attr = unit.attr;
    unit.attr = nullptr;
}

unsigned Wizard::travelDistance() const
{
    return 1;
}

void Wizard::getDamage(unsigned damage)
{
    attr->health -= damage;
}

void Wizard::heal(unsigned hp)
{
    if (attr->health + int(hp) < int(HpTypes::WIZARD))
        attr->health += hp;
    else
        attr->health = int(HpTypes::WIZARD);
}

string Wizard::type() const {return "Wizard";}
