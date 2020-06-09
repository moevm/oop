#ifndef FOREST_H
#define FOREST_H

#include "landscape.h"

class Forest: public Landscape
{
public:
    Forest(){};

    std::string namelandscape() override{
        return "forest";
    }

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
            return true;
        if(unit->type == "MediumWarrior")
            return true;
        if(unit->type == "DistanceWarrior")
            return false;
    }
};

#endif // FOREST_H
