//
// Created by max on 31.03.20.
//

#ifndef OOP_INTERACTION_H
#define OOP_INTERACTION_H

#include "Field.h"
#include <termios.h>
#include <unistd.h>
#include "Base.h"
#include <string>

using std::string;
using std::to_string;

class Interaction {
public:
    Interaction()
    {

    }
    ~Interaction()
    {

    }
    void setBase(Field* f);
    void services(Field* f,Unit* unit,NeutralObject* object, bool &check);
    void repair(Field* f,Base* base, bool &check);
    void attack(Field* f,Unit* curr_unit, bool &check,int x,int y);
    void battleWithUnit(Field* f,bool &check,Unit* unit1, Unit* unit2,int x1,int y1,int x2,int y2);
    void attackBase(Field* f,bool &check,int x1,int x2,int y1,int y2);
    void killUnit(Field* f, Unit* unit,int x,int y);
};


#endif //OOP_INTERACTION_H
