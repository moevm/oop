//
// Created by anton on 27.02.2020.
//

#ifndef OOP_1_FLAMEN_H
#define OOP_1_FLAMEN_H

#include "Wizard.h"

class Flamen: public Wizard {
public:
    Flamen();

    char getClass() const final;
};


#endif //OOP_1_FLAMEN_H
