//
// Created by Evgeniy on 3/10/2020.
//

#ifndef OOP1_3_ARMOREDCAR_H
#define OOP1_3_ARMOREDCAR_H

#include "Transport.h"

class ArmoredCar : public Transport {
public:
    char type() {
        return 'C';
    }

    ArmoredCar(int x, int y){
        this->x=x;
        this->y = y;
        this->param.health=220;
        this->param.armor=150;
        this->param.distance=15;
        this->param.damage = 60;
        this->param.fuel = 60;
    }
};


#endif //OOP1_3_ARMOREDCAR_H
