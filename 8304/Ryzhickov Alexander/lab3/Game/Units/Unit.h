//
// Created by Alex on 21.03.2020.
//

#ifndef GAME_UNIT_H
#define GAME_UNIT_H


#include "../UnitAmunition/Weapon/Weapon.h"
#include "../UnitAmunition/Armor/Armor.h"
#include "UnitInterface.h"
class Base;

class Unit : public UnitInterface {
protected:
    Weapon *unitWeapon; // оружие
    Armor *unitArmor;   // броня
    unsigned health;// здоровье
    unsigned armor;     // показатель брони
    unsigned damage;    // урон
    unsigned moves;     // количество ходов
    unsigned x;
    unsigned y;
    unsigned numerInArmy;
    Base *base;
    unsigned maxHealth;
    unsigned maxArmor;
    unsigned attackBonus = 0;
public:
    unsigned int getAttackBonus() const;

public:
    Unit(int startX, int startY, Weapon*unitWeapon, Armor *unitArmor);

    Unit();

    ~Unit();

    unsigned int getHealth() const;

    unsigned int getArmor() const;

    unsigned int getDamage() const;

    unsigned int getMoves() const;

    unsigned int getX() const;

    unsigned int getY() const;

    unsigned int getNumerInArmy() const;

    unsigned * getArmorForGenerator();

    unsigned * getHealthForGenerator();

    void setNumerInArmy(unsigned int numerInArmy);

    void add(Base *ref);

    void setAttackBonus(unsigned int attackBonus);

protected:
public:
    void setHealth(unsigned int health);

};


#endif //GAME_UNIT_H
