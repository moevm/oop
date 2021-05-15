//
// Created by Evgeniy on 3/10/2020.
//

#ifndef OOP1_3_NEUTRALOBJECT_H
#define OOP1_3_NEUTRALOBJECT_H


#include "../Unit/Unit.h"

class NeutralObject{
public:
    char name;
    virtual void action(Unit *unit) = 0;

    virtual char typeNeutral() = 0;
    void operator>>(Unit* unit){
           action(unit);
        }
};



#endif //OOP1_3_NEUTRALOBJECT_H
