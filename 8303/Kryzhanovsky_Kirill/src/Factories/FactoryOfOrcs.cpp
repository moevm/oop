//
// Created by therealyou on 05.03.2020.
//

#include "FactoryOfOrcs.h"

Troll *FactoryOfOrcs::createTroll() {
    return new Troll();
}

Goblin *FactoryOfOrcs::createGoblin() {
    return new Goblin();
}
