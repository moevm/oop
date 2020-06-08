//
// Created by therealyou on 16.03.2020.
//

#ifndef LAB1_LANDSCAPEPROXY_H
#define LAB1_LANDSCAPEPROXY_H


#include "Landscape.h"

class LandscapeProxy {
private:
    Landscape *landscape;
public:
    LandscapeProxy(Landscape *landscape);
    int getAbsorptionFactor(UnitsType unit);
    int getSlowFactor(UnitsType unit);
};


#endif //LAB1_LANDSCAPEPROXY_H
