//
// Created by therealyou on 10.03.2020.
//

#ifndef LAB1_DESERT_H
#define LAB1_DESERT_H


#include "Landscape.h"

class Desert : public Landscape {
public:
    Desert();

    int getAbsorptionFactor(UnitsType unit) override;

    int getSlowFactor(UnitsType unit) override;
};


#endif //LAB1_DESERT_H
