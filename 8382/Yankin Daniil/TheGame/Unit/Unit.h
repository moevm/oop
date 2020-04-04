#pragma once

#include "IUnit.h"
#include "Trivia/Attributes.h"

class Player;
class Base;
class UnitGroup;


class Unit : public IUnit
{
    friend class UnitGroup;

public:
    Unit(Point point, Base* base);
    ~Unit();

    Point getPoint() override;
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


    virtual double classAttackModifier(Object* enemy) = 0;
    virtual double typeAttackModifier(Object* enemy) = 0;

protected:
    void setPoint(Point point) override;
    void setMovePoints(uint8_t points) override;

    void smallHeal(uint16_t healSize = 10) override;
    void fullHeal() override;
    void attackModification(int16_t modSize) override;
    void armorModification(int16_t modSize) override;
    void renewMovePoints() override;


    Point point;

    union {
        Base* base;
        UnitGroup* group;
    };
    bool isGroup;

    Health health;
    Strength strength;
    Armor armor;
    MovePoints movePoints;
};


enum UnitClasses {
    UNIT_MELEE,
    UNIT_RANGED,
    UNIT_SIEGE_ENGINE
};
