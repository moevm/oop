#ifndef LAND_H
#define LAND_H

#include "landscape.h"

class Land: public Landscape, public Unit
{
public:
    Land(){
        this->type = "landscape";
        this->name = "land";
    };

    bool isMoved(Unit* unit) override{
        if(unit->type == "MeleeWarrior")
            return true;
        if(unit->type == "MediumWarrior")
            return true;
        if(unit->type == "DistanceWarrior")
            return true;
    }

    bool isDamage(Unit* unit) override{
        if(unit->type == "MeleeWarrior")
            return false;
        if(unit->type == "MediumWarrior")
            return false;
        if(unit->type == "DistanceWarrior")
            return false;
    }
};

#endif // LAND_H
