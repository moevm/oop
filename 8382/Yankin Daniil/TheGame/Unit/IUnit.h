#pragma once

#include "Object/Object.h"
#include "Game/Game.h"

class Player;
class Base;


class IUnit : public Object
{
    friend class HealOffice;
    friend class DamageOffice;
    friend class ArmorOffice;
    friend class MovementOffice;
    friend class Game;

public:
    IUnit();

    uint8_t getGroupType() override;
    virtual uint8_t getUnitClass() = 0;

    virtual Player* getPlayer() = 0;
    virtual Base* getBase() = 0;

    virtual uint16_t getMaxHealth() = 0;
    virtual uint16_t getHealth() = 0;
    virtual uint16_t getAttack() = 0;
    virtual uint8_t getAttackRadius() = 0;
    virtual uint16_t getArmor() = 0;
    virtual uint8_t getMaxMovePoints() = 0;
    virtual uint8_t getMovePoints() = 0;

    virtual uint16_t giveDamage(IUnit* enemy) = 0;
    virtual uint16_t giveDamage(Base* enemy) = 0;
    virtual bool takeDamage(uint16_t damage) = 0;

    bool move(Point point);
    void unite(IUnit* passive);

protected:
    virtual void setPoint(Point point) = 0;
    virtual void setMovePoints(uint8_t points) = 0;

    virtual void smallHeal(uint16_t healSize = 10) = 0;
    virtual void fullHeal() = 0;
    virtual void attackModification(int16_t modSize) = 0;
    virtual void armorModification(int16_t modSize) = 0;
    virtual void renewMovePoints() = 0;
};
