//
// Created by anton on 02.03.2020.
//

#ifndef BATTLE_FOR_HONOR_HORSEARCHER_H
#define BATTLE_FOR_HONOR_HORSEARCHER_H


#include "Horseman.h"

class HorseArcher : Horseman {
public:
    HorseArcher(int x, int y){
        this->setHealth(100);
        this->setArmour("light");
        this->setDamage("pierce");
        this->setDistance(1);
        this->setSpeed(1);
        this->setX(x);
        this->setY(y);
        this->setSymbol('H');
    }
};



#endif //BATTLE_FOR_HONOR_HORSEARCHER_H
