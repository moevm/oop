//
// Created by anton on 02.03.2020.
//

#ifndef BATTLE_FOR_HONOR_SPEARHORSE_H
#define BATTLE_FOR_HONOR_SPEARHORSE_H


#include "Horseman.h"

class SpearHorse : Horseman{
    SpearHorse(int x, int y){
        this->health = 100;
        this->armour->set_type("medium");
        this->damage->set_type("pierce");
        this->distance = 1;
        this->speed = 1;
        this->x = x;
        this->y = y;
        this->symbol = 'P';
    }
};

#endif //BATTLE_FOR_HONOR_SPEARHORSE_H
