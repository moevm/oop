//
// Created by andrei on 02.03.2020.
//

#ifndef OOP_LAB1_LIQUID_H
#define OOP_LAB1_LIQUID_H


#include "landscape.h"

class Liquid: public Landscape {
public:
    char getType() override;

private:
    const char type = 'l';
};


#endif //OOP_LAB1_LIQUID_H
