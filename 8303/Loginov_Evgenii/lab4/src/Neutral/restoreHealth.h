//
// Created by Evgeniy on 3/10/2020.
//

#ifndef OOP1_3_RESTOREHEALTH_H
#define OOP1_3_RESTOREHEALTH_H


#include "NeutralObject.h"

    class RestoreHealth {
    public:
        virtual void action(Unit *unit) = 0;

    };

    class RestoreHealthDay : public RestoreHealth {
        void action(Unit *unit) {
            unit->param.armor += 1;
            std::cout<<"health += 1 (day)\n";
        }
    };

    class RestoreHealthNight : public RestoreHealth {
        void action(Unit *unit) {
            int change = 10;
            unit->param.armor += change;
            std::cout<<"health += "<<change<<" (night)\n";
        }
    };

    class RestoreHealthAction : public NeutralObject{
    public:
        RestoreHealthAction(RestoreHealth *strategy) {
            restorehealth = strategy;
        }

    private:

        RestoreHealth *restorehealth;

        void action(Unit *unit) {
            restorehealth->action(unit);
        }

        char typeNeutral(){
            return '4';
        }
    };

#endif //OOP1_3_RESTOREHEALTH_H
