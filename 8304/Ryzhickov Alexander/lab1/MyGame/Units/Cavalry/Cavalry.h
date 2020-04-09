//
// Created by Alex on 16.02.2020.
//
#ifndef MYGAME_CAVALRY_H


#define MYGAME_CAVALRY_H


#include "../Unit.h"

class Cavalry : public Unit {
public:
    Cavalry(int startX, int startY, Weapon *unitWeapon, Armor *unitArmor);
    Cavalry();
};


#endif //MYGAME_CAVALRY_H
