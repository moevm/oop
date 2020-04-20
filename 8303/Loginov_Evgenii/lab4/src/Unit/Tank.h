//
// Created by Evgeniy on 3/10/2020.
//

#ifndef OOP1_3_TANK_H
#define OOP1_3_TANK_H

#include "Transport.h"

class Tank : public Transport {
public:

    Tank(int x, int y){
        this->x=x;
        this->y = y;
        this->param.health=320;
        this->param.armor=170;
        this->param.distance=10;
        this->param.damage = 170;
        this->param.fuel = 1160;
    }
    char type() {
        return 'T';
    }
};

#endif //OOP1_3_TANK_H

