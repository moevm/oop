#include "base.h"

Base::Base(unsigned unitLimit, unsigned number, std::string name, Field *field)
    :unitLimit(unitLimit), unitCounter(0), stability(100), number(number), name(name)
{
    attackFactory = new AttackDevice;
    simpleFactory = new SimpleDevice;
    supportFactory = new SupportDevice;
    createMediator = new CreateMediator(field, this);
    units = new CompositeKeeper;
    for (unsigned i=0; i<3; i++)
    {
        units->addComponent(new CompositeKeeper);
        for (unsigned j=0; j<2; j++)
        {
            units->getComponent(i)->addComponent(new CompositeKeeper);
        }
    }
}

Base::~Base()
{
    delete units;
    delete createMediator;

    delete attackFactory;
    delete supportFactory;
    delete simpleFactory;
}

std::string Base::about()
{
    return "Base named " + name;
}

std::string Base::shortName()
{
    return "BASE";
}

unsigned Base::getNumber()
{
    return number;
}

FieldItem *Base::itemCopy()
{
    return new Base(*this);
}

void Base::sendUnitToField(FieldItem *item, unsigned x, unsigned y)
{
    createMediator->Notify(this, item, x, y);
}

void Base::setGameMediator(IGameMediator *value)
{
    gameMediator = value;
}

//CREATOR

IUnit* Base::createUnit(unsigned x, unsigned y, UnitType type)
{
    if (unitCounter == unitLimit)
    {
        throw std::out_of_range("unit limit reached");
    }
    Unit *newUnit;
    switch (type) {
    case ATT_SC:
        newUnit = attackFactory->createCyberScientist(this);
        break;
    case ATT_BS:
        newUnit = attackFactory->createCyberBerserk(this);
        break;
    case SUP_SC:
        newUnit = supportFactory->createCyberScientist(this);
        break;
    case SUP_BS:
        newUnit = supportFactory->createCyberBerserk(this);
        break;
    case SIM_SC:
        newUnit = simpleFactory->createCyberScientist(this);
        break;
    case SIM_BS:
        newUnit = simpleFactory->createCyberBerserk(this);
    }
    try {
        sendUnitToField(newUnit, x, y);
        gameMediator->Notify(newUnit, true);
    } catch (std::logic_error err) {
        delete newUnit;
        throw err;
    }
    unitCounter++;

    UnitKeeper *unit = new UnitKeeper(newUnit);
    units->getComponent(type/3)->getComponent(type%2)->addComponent(unit);
    return newUnit;
}

std::list<Unit *> Base::getUnitList()
{
    return units->getUnitList();
}

std::list<Unit *> Base::getUnitTypeList(UnitType type)
{
    return units->getComponent(type/3)->getComponent(type%2)->getUnitList();
}

//GETTERS/SETTERS

void Base::setCreateMediator(ICreateMediator *value)
{
    createMediator = value;
}

void Base::deleteUpdate(Unit *unit)
{
    unsigned type = static_cast<unsigned>(unit->getType());
    if (units->getComponent(type/3)->getComponent(type%2)->removeUnitComponent(unit))
        unitCounter--;
    gameMediator->Notify(unit, false);
}

void Base::reduceStability(unsigned value)
{
    if (value >= stability)
        stability = 0;
    else
        stability -= value;
}

unsigned Base::getStability() const
{
    return stability;
}

unsigned Base::getUnitLimit() const
{
    return unitLimit;
}

unsigned Base::getUnitCounter() const
{
    return unitCounter;
}

void Base::setMoveMediator(MoveMediator *value)
{
    moveMediator = value;
}

//MEDIATOR

CreateMediator::CreateMediator(Field *field, Base *base)
    :field(field), base(base)
{
    field->setCreateMediator(this);
    base->setCreateMediator(this);
}

void CreateMediator::Notify(FieldItem *sender, FieldItem *unit, unsigned x, unsigned y)
{
    field->addBaseUnit(x, y, sender, unit);
}
