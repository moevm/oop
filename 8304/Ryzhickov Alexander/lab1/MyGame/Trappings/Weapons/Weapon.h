//
// Created by Alex on 02.03.2020.
//

#ifndef MYGAME_WEAPON_H
#define MYGAME_WEAPON_H


#include "../../enums/attackBonus.h"

class Weapon {
protected:
    int damage;
    int level;
    int cost;
    attackBonus bonus;
public:
    Weapon();
    int getDamage() const;
    virtual void upgradeWeapon(int *costUpgrade) = 0;
};


#endif //MYGAME_WEAPON_H
