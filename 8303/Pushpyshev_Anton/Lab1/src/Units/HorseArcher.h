//
// Created by anton on 02.03.2020.
//

#ifndef BATTLE_FOR_HONOR_HORSEARCHER_H
#define BATTLE_FOR_HONOR_HORSEARCHER_H


#include "Horseman.h"

class HorseArcher : Horseman {
public:
    HorseArcher(int x, int y){
        this->health = 100;
        this->armour->set_type("light");
        this->damage->set_type("pierce");
        this->distance = 1;
        this->speed = 1;
        this->x = x;
        this->y = y;
        this->symbol = 'H';
    }
};



#endif //BATTLE_FOR_HONOR_HORSEARCHER_H
