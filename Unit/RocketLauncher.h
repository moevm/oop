//
// Created by Evgeniy on 3/10/2020.
//

#ifndef OOP1_3_ROCKETLAUNCHER_H
#define OOP1_3_ROCKETLAUNCHER_H

#include "RangedFighter.h"

class RocketLauncher : public RangedFighter {
public:
    char type() {
        return 'L';
    }
    RocketLauncher(int x, int y){
        this->x=x;
        this->y = y;
        this->param.health=150;
        this->param.armor=100;
        this->param.distance=1;
        this->param.damage = 30;
    }
};

#endif //OOP1_3_ROCKETLAUNCHER_H
