//
// Created by Evgeniy on 3/10/2020.
//

#ifndef OOP1_3_RESTOREARMOUR_H
#define OOP1_3_RESTOREARMOUR_H


#include "NeutralObject.h"

class restoreArmour : public NeutralObject{
    void action(Unit *unit) {
        unit->param.armor += 1;
        std::cout<<"armour++\n";
    }

    char typeNeutral(){
        return '2';
    }
};


#endif //OOP1_3_RESTOREARMOUR_H
