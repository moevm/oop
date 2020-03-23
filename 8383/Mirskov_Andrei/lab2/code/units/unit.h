//
// Created by andrei on 19.02.2020.
//

#ifndef OOP_LAB1_UNIT_H
#define OOP_LAB1_UNIT_H


#include "../atributes/health.h"
#include "../atributes/armor.h"
#include "../atributes/damage.h"
#include "../neutral/neutral.h"
#include "../neutral/clothes.h"
#include "../neutral/potion.h"
#include "../neutral/weapon.h"
#include "../neutral/kit.h"

class Unit {
public:
    virtual int getHealth() = 0;

    virtual void heal(int health) = 0;

    virtual bool takeDamage(int damage) = 0;

    virtual int getArmor() = 0;

    virtual void setArmor(int armor) = 0;

    virtual int getDamage() = 0;

    virtual void setDamage(int damage) = 0;

    virtual int getX() = 0;

    virtual void setX(int newX) = 0;

    virtual int getY() = 0;

    virtual void setY(int newY) = 0;

    virtual void takeItem(Clothes*) = 0;

    virtual void takeItem(Potion*) = 0;

    virtual void takeItem(Weapon*) = 0;

    virtual void takeItem(Kit*) = 0;

    virtual void operator += (Neutral*) = 0;

    virtual char getType() = 0;


};


#endif //OOP_LAB1_UNIT_H
