//
// Created by therealyou on 05.03.2020.
//

#include "FactoryOfAlliance.h"

Shooter *FactoryOfAlliance::createShooter() {
    return new Shooter();
}

Peon *FactoryOfAlliance::createPeon() {
    return new Peon();
}
