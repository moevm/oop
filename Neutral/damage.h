//
// Created by Evgeniy on 3/10/2020.
//

#ifndef OOP1_3_DAMAGE_H
#define OOP1_3_DAMAGE_H

#include "NeutralObject.h"

class Damage : public NeutralObject{
    void action(Unit *unit) {
        std::cout<<"damage++\n";
    }

    char typeNeutral(){
        return '1';
    }
};

#endif //OOP1_3_RESTOREARMOUR_H
