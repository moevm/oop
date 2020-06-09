//
// Created by Evgeniy on 3/10/2020.
//

#ifndef OOP1_3_RESTOREFUEL_H
#define OOP1_3_RESTOREFUEL_H

#include "NeutralObject.h"

//class RestoreFuel  : public NeutralObject{
//    void action(Unit *unit) {
//        unit->param.fuel += 1;
//        std::cout<<"fuel++\n";
//    }

//    char typeNeutral(){
//        return '3';
//    }
//};

class restoreFuel{
public:
    virtual void action(Unit *unit)= 0;
};

class restoreFuelDay : public restoreFuel{
    void action(Unit *unit){
        unit->param.fuel +=2;
         std::cout<<"fuel +=2 (day)\n";
    }
};

class restoreFuelNight : public restoreFuel{
    void action(Unit *unit) {
        unit->param.fuel += 12;
         std::cout<<"fuel +=12 (night)\n";
    }
};

class restoreFuelAction : public NeutralObject{
public:
    restoreFuelAction(restoreFuel *strategy){
        restorefuel = strategy;
    }
private:
    restoreFuel *restorefuel;

    void action(Unit *unit) {
        restorefuel->action(unit);
    }

        char typeNeutral(){
            return '3';
        }
};

#endif //OOP1_3_RESTOREFUEL_H
