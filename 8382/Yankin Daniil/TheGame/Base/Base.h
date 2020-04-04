#pragma once

#include <set>
#include "Object/Object.h"
#include "Unit/UnitHeader.h"

class Player;
class Cell;

class Base : public Object
{
public:
    Base(Point point, Player* player);
    ~Base();

    uint8_t getGroupType() override;
    uint8_t getObjectType() override;

    Player* getPlayer();
    Point getPoint() override;

    uint16_t getMaxHealth();
    uint16_t getHealth();
    uint16_t getAttack();
    uint16_t getArmor();

    uint16_t giveDamage(IUnit *enemy);
    bool takeDamage(uint16_t damage);

    void produceUnit(uint8_t unitType);

    bool isBelowUnitMax();
    void addUnit(IUnit* unit);
    void removeUnit(IUnit* unit);

    uint8_t getUnitCount();
    uint8_t getMaxUnitCount();

private:
    Point point;

    Player* player;
    Health health;
    Strength strength;
    Armor armor;

    UnitFactory unitFactory;
    std::set <IUnit*> unitSet;
    uint8_t maxUnitCount;
};
