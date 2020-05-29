//
// Created by andrei on 19.02.2020.
//

#ifndef OOP_LAB1_UNIT_H
#define OOP_LAB1_UNIT_H

#include "../atributes/health.h"
#include "../atributes/armor.h"
#include "../atributes/damage.h"
#include "../neutral/neutral.h"

class Neutral;

class Unit {
public:
    virtual ~Unit() = 0;

    virtual int getHealth() = 0;

    virtual void heal(int health) = 0;

    virtual bool takeDamage(int damage) = 0;

    virtual int getArmor() = 0;

    virtual void setArmor(int armor) = 0;

    virtual int getDamage() = 0;

    virtual void setDamage(int damage) = 0;

    virtual void operator += (Neutral*) = 0;

    virtual char getType() = 0;

    virtual void notify() = 0;

    virtual int getBaseNum() = 0;
};


#endif //OOP_LAB1_UNIT_H
