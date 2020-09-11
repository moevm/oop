//
// Created by Evgeniy on 3/10/2020.
//

#ifndef OOP1_3_RESTOREARMOUR_H
#define OOP1_3_RESTOREARMOUR_H


#include "NeutralObject.h"

class RestoreArmour {
public:
    virtual void action(Unit *unit) = 0;
    virtual ~RestoreArmour() {}
};

class RestoreArmourDay : public RestoreArmour {
    void action(Unit *unit) {
        unit->param.armor += 1;
        std::cout<<"armour += 1 (day)\n";
    }
};

class RestoreArmourNight : public RestoreArmour {
    void action(Unit *unit) {
        int change = 10;
        unit->param.armor += change;
        std::cout<<"armour += "<<change<<" (night)\n";
    }
};

class RestoreArmourAction : public NeutralObject{
public:
    RestoreArmourAction(RestoreArmour *strategy) {
        restoreArmour = strategy;
    }

private:

    RestoreArmour *restoreArmour;

    void action(Unit *unit) {
        restoreArmour->action(unit);
    }

    char typeNeutral(){
        return '2';
    }
};


#endif //OOP1_3_RESTOREARMOUR_H
