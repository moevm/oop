//
// Created by Evgeniy on 3/10/2020.
//

#ifndef OOP1_3_RESTOREFUEL_H
#define OOP1_3_RESTOREFUEL_H

#include "NeutralObject.h"

class restoreFuel  : public NeutralObject{
    void action(Unit *unit) {
        unit->param.fuel += 1;
        std::cout<<"fuel++\n";
    }

    char typeNeutral(){
        return '3';
    }
};


#endif //OOP1_3_RESTOREFUEL_H
