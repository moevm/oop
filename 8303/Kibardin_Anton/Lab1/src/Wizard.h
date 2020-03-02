//
// Created by anton on 27.02.2020.
//

#ifndef OOP_1_WIZARD_H
#define OOP_1_WIZARD_H

#include "Unit.h"

class Wizard: public Unit {
public:
    char getClass() const;
    friend class Flamen;
    friend class Necromancer;
};


#endif //OOP_1_WIZARD_H
