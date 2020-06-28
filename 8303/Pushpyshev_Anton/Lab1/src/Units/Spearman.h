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
        this->health = 90;
        this->armour->set_type("light");
        this->damage->set_type("light");
        this->distance = 1;
        this->speed = 1;
        this->x = x;
        this->y = y;
        this->symbol = 180;
    }
};


#endif //BATTLE_FOR_HONOR_SPEARMAN_H
