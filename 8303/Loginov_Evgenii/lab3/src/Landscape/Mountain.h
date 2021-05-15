//
// Created by Evgeniy on 3/10/2020.
//

#ifndef OOP1_3_MOUNTAIN_H
#define OOP1_3_MOUNTAIN_H

#include "Landscape.h"

class Mountain : public Landscape{
public:
    Mountain(){
    }

    char typeLandscape() override{
        return '^';
    }

    bool canMove(Unit *unit) override {
        switch(unit->type()) {
        case 'C' :
        case 'T' :
            return false;
        case 'M' :
        case 'R' :
        case 'L' :
        case 'S':
            return true;
        }
    }

};
#endif //OOP1_3_MOUNTAIN_H
