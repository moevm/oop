//
// Created by Evgeniy on 3/10/2020.
//

#ifndef OOP1_3_MEDIC_H
#define OOP1_3_MEDIC_H

#include "Footman.h"

class Medic: public Footman {
public:
    char type() {
        return 'M';
    }
    Medic(int x, int y){
        this->x=x;
        this->y = y;
        this->param.health=120;
        this->param.armor=64;
        this->param.distance=4;
        this->param.damage = 25;
    }
};

#endif //OOP1_3_MEDIC_H
