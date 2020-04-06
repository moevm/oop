//
// Created by anton on 27.02.2020.
//

#ifndef OOP_1_BARD_H
#define OOP_1_BARD_H


#include "Thief.h"

class Bard: public Thief {
public:
    Bard();

    char getClass() const final;
};


#endif //OOP_1_BARD_H
