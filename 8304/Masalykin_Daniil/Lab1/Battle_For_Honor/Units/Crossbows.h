//
// Created by anton on 02.03.2020.
//

#ifndef BATTLE_FOR_HONOR_CROSSBOWS_H
#define BATTLE_FOR_HONOR_CROSSBOWS_H


#include "Archer.h"

class Crossbows : Archer{
    Crossbows(int x, int y){
        this->setHealth(100);
        this->setArmour("hard");
        this->setDamage("hard");
        this->setDistance(1);
        this->setSpeed(1);
        this->setX(x);
        this->setY(y);
        this->setSymbol('C');
    }
};


#endif //BATTLE_FOR_HONOR_CROSSBOWS_H
