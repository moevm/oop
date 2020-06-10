#include "Base.h"
#include <QDebug>

Base::Base(string name, unsigned maxNumUnits, unsigned p) : Object(name), maxNumUnits(maxNumUnits)
{
    player = p;
    attr = new Attributes(HpTypes::BASE, RngTypes::BASE, DmgTypes::BASE,
                          ArmTypes::BASE, ManaTypes::BASE);
}

bool Base::createUnit(Unit* unit)
{
    if (barrack.size() == maxNumUnits)
        return false;

    barrack.add(unit);

    return true;
}

Unit* Base::getUnit()
{
    auto unit = barrack.extractUnit();
    unit->player = player;
    return unit;
}

bool Base::empty() const
{
    return barrack.empty();
}

unsigned Base::travelDistance() const
{
    return 0;
}

void Base::attack()
{
    mediator->attack(this);
}

void Base::getDamage(unsigned damage)
{
    attr->health -= damage;
}

void Base::heal(unsigned hp)
{
    if (attr->health + int(hp) < int(HpTypes::BASE))
        attr->health += hp;
    else
        attr->health = int(HpTypes::BASE);
}

const HeapUnit& Base::getHeap() const
{
    return barrack;
}

string Base::type() const { return "Base"; }

Base::~Base()
{
    delete attr;
    attr = nullptr;
    while (!barrack.empty())
        delete barrack.extractUnit();
}
