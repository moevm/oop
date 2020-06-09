#ifndef SWAMP_H
#define SWAMP_H

#include "landscape.h"

class Swamp: public Landscape
{
public:
    Swamp(){};

    std::string namelandscape() override{
        return "swamp";
    }

    bool isMoved(Unit* unit) override{
        if(unit->type == "MeleeWarrior")
            return false;
        if(unit->type == "MediumWarrior")
            return false;
        if(unit->type == "DistanceWarrior")
            return true;
    }

    bool isDamage(Unit* unit) override{
        if(unit->type == "MeleeWarrior")
            return true;
        if(unit->type == "MediumWarrior")
            return true;
        if(unit->type == "DistanceWarrior")
            return false;
    }
};

#endif // SWAMP_H
