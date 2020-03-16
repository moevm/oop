//
// Created by Глебушунок on 15.03.2020.
//

#ifndef OOP_LAB1_LANDSCAPEPROXY_H
#define OOP_LAB1_LANDSCAPEPROXY_H

#include "Landscape.h"
#include "Point.h"
#include "GameField.h"

class LandscapeProxy {

private:

    Landscape *landscape;

public:

    LandscapeProxy(Landscape *landscape);

    int getDamageFactor(WeaponType type);
    int getAbsorptionFactor(ArmorType type);

};
#endif //OOP_LAB1_LANDSCAPEPROXY_H
