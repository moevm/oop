//
// Created by shenk on 01.03.2020.
//

#ifndef UNTITLED13_LANDSCAPE_H
#define UNTITLED13_LANDSCAPE_H


#include "../Weapon/Weapon.h"
#include "../Armor/Armor.h"

class Landscape {

public:

    virtual int getDamageFactor(WeaponType type) = 0;
    virtual int getAbsorptionFactor(ArmorType type) = 0;

};


#endif //UNTITLED13_LANDSCAPE_H
