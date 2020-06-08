//
// Created by therealyou on 10.03.2020.
//

#ifndef LAB1_WOOD_H
#define LAB1_WOOD_H


#include "Landscape.h"

class Wood : public Landscape {
public:
    Wood();

    int getAbsorptionFactor(UnitsType unit);

    int getSlowFactor(UnitsType unit);

};


#endif //LAB1_WOOD_H
