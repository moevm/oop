//
// Created by therealyou on 10.03.2020.
//

#ifndef LAB1_MOUNTAIN_H
#define LAB1_MOUNTAIN_H


#include "Landscape.h"

class Mountain : public Landscape {
public:
    Mountain();

    int getAbsorptionFactor(UnitsType unit) override;

    int getSlowFactor(UnitsType unit) override;

};


#endif //LAB1_MOUNTAIN_H
