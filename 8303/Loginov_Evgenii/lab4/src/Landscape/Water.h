//
// Created by Evgeniy on 3/10/2020.
//

#ifndef OOP1_3_WATER_H
#define OOP1_3_WATER_H

#include "Landscape.h"

class Water : public Landscape{
public:
    Water(){
    }

    char typeLandscape() override{
        return '~';
    }

    bool canMove(Unit *unit) override{
        switch(unit->type()) {
        case 'C' :
        case 'T' :
            return false;
        case 'M' :
        case 'R' :
            return true;
        case 'L' :
        case 'S':
            return false;
        }
    }
};

#endif //OOP1_3_WATER_H
