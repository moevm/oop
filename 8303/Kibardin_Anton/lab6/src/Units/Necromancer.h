//
// Created by anton on 27.02.2020.
//

#ifndef OOP_1_NECROMANCER_H
#define OOP_1_NECROMANCER_H

#include "Wizard.h"

class Necromancer: public Wizard {
public:
    Necromancer();

    Necromancer(Specifications);

    char getClass() const final;

};


#endif //OOP_1_NECROMANCER_H
