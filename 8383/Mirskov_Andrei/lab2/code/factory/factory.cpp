//
// Created by andrei on 26.02.2020.
//

#include "factory.h"

Unit *Factory::createUnit(Base* base, char type) {
    switch (type) {
        case 'E':
            return new ElephantMan(base);
        case 'H':
            return new HorseMan(base);
        case 'F':
            return new FireArcher(base);
        case 'M':
            return new SpearMan(base);
        case 'S':
            return new SwordMan(base);
        case 'W':
            return new WoodenArcher(base);
        default: ;

    }
}

Neutral *Factory::createNeutral(char type) {
    switch (type) {
        case 'c':
            return new Clothes;
        case 'p':
            return new Potion;
        case 'w':
            return new Weapon;
        case 'k':
            return new Kit;
        default: ;
    }
}





