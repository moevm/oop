//
// Created by anton on 02.03.2020.
//

#ifndef BATTLE_FOR_HONOR_LONGBOWMAN_H
#define BATTLE_FOR_HONOR_LONGBOWMAN_H


#include "Archer.h"

class LongBowman : Archer {
    LongBowman(int x, int y){
        this->setHealth(100);
        this->setArmour("medium");
        this->setDamage("hard");
        this->setDistance(1);
        this->setSpeed(1);
        this->setX(x);
        this->setY(y);
        this->setSymbol('8');
    }
};


#endif //BATTLE_FOR_HONOR_LONGBOWMAN_H
