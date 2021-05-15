//
// Created by Evgeniy on 3/10/2020.
//

#ifndef OOP1_3_RIFLEMAN_H
#define OOP1_3_RIFLEMAN_H

#include "Footman.h"

class Rifleman : public Footman {
public:
    char type() {
        return 'R';
    }

    Rifleman(int x, int y){
        this->x=x;
        this->y = y;
        this->param.health=120;
        this->param.armor=95;
        this->param.distance=3;
        this->param.damage = 33;
    }
};
#endif //OOP1_3_RIFLEMAN_H
