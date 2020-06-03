#ifndef LABS_MOUNTAIN_H
#define LABS_MOUNTAIN_H

#include "Landscape.h"

class Mountain : public Landscape{
public:
    Mountain() {}

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
#endif //LABS_MOUNTAIN_H
