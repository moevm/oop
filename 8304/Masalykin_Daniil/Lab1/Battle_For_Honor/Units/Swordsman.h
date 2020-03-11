//
// Created by anton on 02.03.2020.
//

#ifndef BATTLE_FOR_HONOR_SWORDSMAN_H
#define BATTLE_FOR_HONOR_SWORDSMAN_H


#include "Footman.h"

class Swordsman : public Footman {
public:
    Swordsman(int x, int y){
        this->setHealth(100);
        this->setArmour("medium");
        this->setDamage("pierce");
        this->setDistance(1);
        this->setSpeed(1);
        this->setX(x);
        this->setY(y);
        this->setSymbol('S');
    }
};


#endif //BATTLE_FOR_HONOR_SWORDSMAN_H
