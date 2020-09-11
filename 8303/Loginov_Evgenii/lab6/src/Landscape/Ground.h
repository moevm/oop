//
// Created by Evgeniy on 3/10/2020.
//

#ifndef OOP1_3_GROUND_H
#define OOP1_3_GROUND_H

#include "Landscape.h"
#include "../Unit/Tank.h"

class Ground: public Landscape{
public:
    Ground(){
    }

    char typeLandscape() override{
        return '.';
    }

    bool canMove(Unit *unit) override{
        switch(unit->type()) {
        case 'C' :
        case 'T' :
        case 'M' :
        case 'R' :
        case 'L' :
        case 'S':
            return true;
        }
    }
};

#endif //OOP1_3_GROUND_H
