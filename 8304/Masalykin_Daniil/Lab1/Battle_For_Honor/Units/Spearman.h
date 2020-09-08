//
// Created by anton on 02.03.2020.
//

#ifndef BATTLE_FOR_HONOR_SPEARMAN_H
#define BATTLE_FOR_HONOR_SPEARMAN_H


#include "Footman.h"

class Spearman : public Footman{
public:
    Spearman(int x, int y)
    {
        this->setHealth(90);
        this->setArmour("light");
        this->setDamage("light");
        this->setDistance(1);
        this->setSpeed(1);
        this->setX(x);
        this->setY(y);
        this->setSymbol(180);
    }
};


#endif //BATTLE_FOR_HONOR_SPEARMAN_H
