//
// Created by therealyou on 10.03.2020.
//

#ifndef LAB1_LANDSCAPE_H
#define LAB1_LANDSCAPE_H


#include "../Units/UnitsType.h"
//enum UnitsType


enum Landscapes{
    DESERT,
    MOUNTAIN,
    WOOD
};

class Landscape {

public:
    virtual int getAbsorptionFactor(UnitsType unit) = 0;
    virtual int getSlowFactor(UnitsType unit) = 0;

};


#endif //LAB1_LANDSCAPE_H
