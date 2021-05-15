//
// Created by Evgeniy on 3/10/2020.
//

#ifndef OOP1_3_NONE_H
#define OOP1_3_NONE_H

#include "NeutralObject.h"

class NoneObj : public NeutralObject{
    void action(Unit *unit) {

    }

    char typeNeutral(){
        return ' ';
    }
};

#endif //OOP1_3_RESTOREARMOUR_H
