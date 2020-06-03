
#include "Base.hpp"

Base::Base(std::string playerID, std::string ID, unsigned int maxQuantityOfUnits, double health, double armor, CombatObjectTypeFactory *combatObjectTypeFactory)
{

    this->health = health;
    this->maxQuantityOfUnits = maxQuantityOfUnits;
    this->quantityOfUnits = 0;
    this->playerID = playerID;
    this->ID = ID;
    type = combatObjectTypeFactory->getCombatObjectType(80, 40, 1);
    objectType = BASE;
}

Base::~Base()
{
    armyOfUnits.clear();
}

bool Base::isMoveable() { return false; }

Unit *Base::createUnit(unsigned int type, std::string unitID, CombatObjectTypeFactory *combatObjectTypeFactory)
{
    if (quantityOfUnits == maxQuantityOfUnits)
    {
        
        
        
        throw(Except("The maximum number of units in the Base has already been created", "Base::createUnit(unsigned int type, std::string unitID, CombatObjectTypeFactory *combatObjectTypeFactory)", 0));

        return nullptr;
    }
    Unit *newUnit = nullptr;

    quantityOfUnits++;
    if (type == ARCH_DPS || type == INF_DPS || type == CAV_DPS)
        newUnit = factoryUnit(new UnitDPSFactory, type, unitID, combatObjectTypeFactory);
    else if (type == ARCH_TANK || type == INF_TANK || type == CAV_TANK)
        newUnit = factoryUnit(new UnitTankFactory, type, unitID, combatObjectTypeFactory);
    else
    {

        
        
        
        throw(Except("Unknown unit type", "Base::createUnit(unsigned int type, std::string unitID, CombatObjectTypeFactory *combatObjectTypeFactory)", 0));

        return nullptr;
    }

    armyOfUnits.push_back(newUnit);
    newUnit->attachEvent("object death", this);
    return newUnit;
}

unsigned int Base::getArmyQuantity() { return armyOfUnits.size(); }

void Base::removeUnit(Unit *unit)
{
    std::__1::__wrap_iter<Unit **> index = std::find(armyOfUnits.begin(), armyOfUnits.end(), unit);
    if (index != armyOfUnits.end())
        armyOfUnits.erase(index);
}

void Base::unitDie(Unit *unit)
{
    removeUnit(unit);
    delete unit;
}

Unit *Base::factoryUnit(UnitTankFactory *factory, unsigned int type, std::string unitID, CombatObjectTypeFactory *combatObjectTypeFactory)
{

    if (type == ARCH_TANK || type == ARCH_DPS)
        return factory->createArcher(playerID, unitID, combatObjectTypeFactory);
    if (type == INF_TANK || type == INF_DPS)
        return factory->createInfantry(playerID, unitID, combatObjectTypeFactory);
    if (type == CAV_TANK || type == CAV_DPS)
        return factory->createCavalry(playerID, unitID, combatObjectTypeFactory);
    
    throw(Except("Unknown unit class", "Base::factoryUnit(UnitTankFactory *factory, unsigned int type, std::string unitID, CombatObjectTypeFactory *combatObjectTypeFactory)", 0));

    return nullptr;
}

Unit *Base::factoryUnit(UnitDPSFactory *factory, unsigned int type, std::string unitID, CombatObjectTypeFactory *combatObjectTypeFactory)
{

    if (type == ARCH_TANK || type == ARCH_DPS)
        return factory->createArcher(playerID, unitID, combatObjectTypeFactory);
    if (type == INF_TANK || type == INF_DPS)
        return factory->createInfantry(playerID, unitID, combatObjectTypeFactory);
    if (type == CAV_TANK || type == CAV_DPS)
        return factory->createCavalry(playerID, unitID, combatObjectTypeFactory);
    
    throw(Except("Unknown unit class", "Base::factoryUnit(UnitDPSFactory *factory, unsigned int type, std::string unitID, CombatObjectTypeFactory *combatObjectTypeFactory)", 0));

    return nullptr;
}

void Base::operator+(Object *object) {}
void Base::death() { fireEvent("object death"); };

void Base::eventHandler(Event *event)
{
    if (event->getSEventId() == "object death")
    {
        removeUnit((Unit *)event->getSource());
    }
}

v8::Local<v8::Object> Base::getFullInfo()
{
    v8::Local<v8::Object> info = CombatObject::getFullInfo();
    SetObjProperty(info, "type", objectType);
    return info;
}