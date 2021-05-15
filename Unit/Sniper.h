//
// Created by Evgeniy on 3/10/2020.
//

#ifndef OOP1_3_SNIPER_H
#define OOP1_3_SNIPER_H

#include "RangedFighter.h"

class Sniper : public RangedFighter {
public:
    char type() {
        return 'S';
    }

    Sniper(int x, int y){
        this->x=x;
        this->y = y;
        this->param.health=90;
        this->param.armor=55;
        this->param.distance=3;
        this->param.damage = 30;
    }
};
#endif //OOP1_3_SNIPER_H
