#include "Wizard.h"
#include <utility>
#include <QDebug>

Wizard::Wizard(std::string name) : LongRange(std::move(name)) {
    attr = new Attributes(HpTypes::WIZARD, RngTypes::WIZARD, DmgTypes::WIZARD,
                          ArmTypes::WIZARD, ManaTypes::WIZARD);
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

std::string Wizard::type() const {return "Wizard";}
