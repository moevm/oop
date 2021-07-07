//
// Created by anton on 27.02.2020.
//

#ifndef OOP_1_THIEF_H
#define OOP_1_THIEF_H

#include "Unit.h"

class Thief: public Unit{
    friend class Bard;
    friend class Elf;
};


#endif //OOP_1_THIEF_H
