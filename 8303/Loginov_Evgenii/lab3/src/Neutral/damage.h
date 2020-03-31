//
// Created by Evgeniy on 3/10/2020.
//

#ifndef OOP1_3_DAMAGE_H
#define OOP1_3_DAMAGE_H

#include "NeutralObject.h"



class incDamage {
public:
    virtual void action(Unit *unit) = 0;
};

class incDamageDay : public incDamage{
    void action(Unit *unit){
        unit->param.damage += 1;
        std::cout<<"damage has been increased(day)";
    }
};

class indDamageNight: public incDamage {
    void action(Unit *unit) {
        unit->param.damage += 10;
        std::cout<<"damage has been increased(night)";
    }
};

class incDamageAction : public NeutralObject{
public:
    incDamageAction(incDamage *strategy){
        incdamage = strategy;
    }
private:
    incDamage *incdamage;

    void action(Unit *unit) {
        incdamage->action(unit);
    }

    char typeNeutral(){
            return '1';
        }

};



#endif //OOP1_3_RESTOREARMOUR_H
