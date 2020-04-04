#pragma once

#include <vector>
#include <set>
#include <cmath>
#include "Unit.h"


class UnitGroup : public IUnit
{
public:
    UnitGroup(std::vector <Unit*> details);
    ~UnitGroup();

    uint8_t getUnitClass() override;
    uint8_t getObjectType() override;

    Point getPoint() override;
    void setPoint(Point point) override;
    Player* getPlayer() override;
    Base* getBase() override;

    uint16_t getMaxHealth() override;
    uint16_t getHealth() override;
    uint16_t getAttack() override;
    uint8_t getAttackRadius() override;
    uint16_t getArmor() override;
    uint8_t getMaxMovePoints() override;
    uint8_t getMovePoints() override;

    uint16_t giveDamage(IUnit* enemy) override;
    uint16_t giveDamage(Base* enemy) override;
    bool takeDamage(uint16_t damage) override;

    void join(Unit* unit, bool moveTo);
    void join(UnitGroup* group, bool moveTo);

    uint8_t getMaxGroupSize();
    uint8_t getGroupSize();

    //void unitWasDestructed(Unit* unit);

private:
    void setMovePoints(uint8_t points) override;

    void smallHeal(uint16_t healSize = 10) override;
    void fullHeal() override;
    void attackModification(int16_t modSize) override;
    void armorModification(int16_t modSize) override;
    void renewMovePoints() override;

    std::set <Unit*> unitSet;
    uint8_t maxGroupSize;

    Base* base;
};
