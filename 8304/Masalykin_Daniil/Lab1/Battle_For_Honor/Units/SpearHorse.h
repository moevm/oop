//
// Created by anton on 02.03.2020.
//

#ifndef BATTLE_FOR_HONOR_SPEARHORSE_H
#define BATTLE_FOR_HONOR_SPEARHORSE_H


#include "Horseman.h"

class SpearHorse : Horseman{
    SpearHorse(int x, int y){
        this->setHealth(100);
        this->setArmour("medium");
        this->setDamage("pierce");
        this->setDistance(1);
        this->setSpeed(1);
        this->setX(x);
        this->setY(y);
        this->setSymbol('P');
    }
};

#endif //BATTLE_FOR_HONOR_SPEARHORSE_H
