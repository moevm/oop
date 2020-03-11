//
// Created by Evgeniy on 3/10/2020.
//

#ifndef OOP1_3_RESTOREHEALTH_H
#define OOP1_3_RESTOREHEALTH_H


#include "NeutralObject.h"

class restoreHealth  : public NeutralObject{
    void action(Unit *unit) {
        unit->param.health += 10;
        std::cout<<"health++\n";
    }

    char typeNeutral(){
        return '4';
    }
};


#endif //OOP1_3_RESTOREHEALTH_H
