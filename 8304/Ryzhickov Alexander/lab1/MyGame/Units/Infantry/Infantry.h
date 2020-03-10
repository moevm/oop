//
// Created by Alex on 16.02.2020.
//
#ifndef MYGAME_INFANTRY_H

#define MYGAME_INFANTRY_H


#include "../Unit.h"

class Infantry : public Unit {
public:
    Infantry(int startX, int startY, Weapon*unitWeapon, Armor *unitArmor);
    Infantry();
    virtual void stronger() = 0;
};


#endif //MYGAME_INFANTRY_H
