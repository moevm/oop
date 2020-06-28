//
// Created by anton on 02.03.2020.
//

#ifndef BATTLE_FOR_HONOR_LONGBOWMAN_H
#define BATTLE_FOR_HONOR_LONGBOWMAN_H


#include "Archer.h"

class LongBowman : Archer {
    LongBowman(int x, int y){
        this->health = 100;
        this->armour->set_type("medium");
        this->damage->set_type("hard");
        this->distance = 1;
        this->speed = 1;
        this->x = x;
        this->y = y;
        this->symbol = '8';
    }
};


#endif //BATTLE_FOR_HONOR_LONGBOWMAN_H
