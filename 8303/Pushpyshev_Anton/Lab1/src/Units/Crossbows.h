//
// Created by anton on 02.03.2020.
//

#ifndef BATTLE_FOR_HONOR_CROSSBOWS_H
#define BATTLE_FOR_HONOR_CROSSBOWS_H


#include "Archer.h"

class Crossbows : Archer{
    Crossbows(int x, int y){
        this->health = 100;
        this->armour->set_type("hard");
        this->damage->set_type("hard");
        this->distance = 1;
        this->speed = 1;
        this->x = x;
        this->y = y;
        this->symbol = 'C';
    }
};


#endif //BATTLE_FOR_HONOR_CROSSBOWS_H
