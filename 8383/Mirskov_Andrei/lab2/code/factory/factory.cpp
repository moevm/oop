//
// Created by andrei on 26.02.2020.
//

#include "factory.h"

Unit *Factory::createUnit(int x, int y, char type) {
    switch (type) {
        case 'E':
            return new ElephantMan(x,y);
        case 'H':
            return new HorseMan(x,y);
        case 'F':
            return new FireArcher(x,y);
        case 'M':
            return new SpearMan(x,y);
        case 'S':
            return new SwordMan(x,y);
        case 'W':
            return new WoodenArcher(x,y);
        default: ;

    }
}

Neutral *Factory::createNeutral(int x, int y, char type) {
    switch (type) {
        case 'c':
            return new Clothes(x, y);
        case 'p':
            return new Potion(x, y);
        case 'w':
            return new Weapon(x, y);
        case 'k':
            return new Kit(x,y);
        default: ;
    }
}





