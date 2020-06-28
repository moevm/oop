//
// Created by anton on 02.03.2020.
//

#ifndef BATTLE_FOR_HONOR_SWORDSMAN_H
#define BATTLE_FOR_HONOR_SWORDSMAN_H


#include "Footman.h"

class Swordsman : public Footman {
public:
    Swordsman(int x, int y){
        this->health = 100;
        this->armour->set_type("medium");
        this->damage->set_type("pierce");
        this->distance = 1;
        this->speed = 1;
        this->x = x;
        this->y = y;
        this->symbol = 'S';
    }
};


#endif //BATTLE_FOR_HONOR_SWORDSMAN_H
