//
// Created by therealyou on 05.03.2020.
//

#ifndef LAB1_FACTORYOFALLIANCE_H
#define LAB1_FACTORYOFALLIANCE_H


#include "FactoryOfUnits.h"
#include "../Units/Peon.h"
#include "../Units/Shooter.h"

class FactoryOfAlliance : public FactoryOfUnits{
public:
    Peon* createPeon();
    Shooter* createShooter();
};


#endif //LAB1_FACTORYOFALLIANCE_H
