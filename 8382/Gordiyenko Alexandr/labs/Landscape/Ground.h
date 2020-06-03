#ifndef LABS_GROUND_H
#define LABS_GROUND_H

#include "Landscape.h"
#include "../Units/Necromancer.h"

class Ground: public Landscape{
public:
    Ground() {}
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

#endif //LABS_GROUND_H
