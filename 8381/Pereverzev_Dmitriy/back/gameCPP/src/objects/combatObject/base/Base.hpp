

#ifndef Base_hpp
#define Base_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include "../CombatObject.hpp"

#include "../unit/unitFactory/UnitTankFactory.hpp"
#include "../unit/unitFactory/UnitDPSFactory.hpp"
#include "../CombatObjectTypeFactory.hpp"
#include "../../../TypeСonstants.hpp"

class Unit;

class Base : public CombatObject
{
private:
    std::vector<Unit *> armyOfUnits;
    unsigned int maxQuantityOfUnits;
    unsigned int quantityOfUnits;

    Unit *factoryUnit(UnitTankFactory *factory, unsigned int type, std::string unitID, CombatObjectTypeFactory *combatObjectTypeFactory);
    Unit *factoryUnit(UnitDPSFactory *factory, unsigned int type, std::string unitID, CombatObjectTypeFactory *combatObjectTypeFactory);

    void removeUnit(Unit *unit);
    void death() override; 
    void unitDie(Unit *unit);

public:
    Base(std::string playerID, std::string ID, unsigned int maxQuantityOfUnits, double health, double armor, CombatObjectTypeFactory *combatObjectTypeFactory);
    ~Base();
    bool isMoveable() override;
    Unit *createUnit(unsigned int type, std::string unitID, CombatObjectTypeFactory *combatObjectTypeFactory);
    unsigned int getArmyQuantity();

    
    
    
    
    
    
    void operator+(Object *object) override;
    
    
    v8::Local<v8::Object> getFullInfo() override;

    /*  */
    void eventHandler(Event *event) override;
    /*  */
};

#endif /* Base_hpp */
