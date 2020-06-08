//
// Created by therealyou on 11.02.2020.
//

#include "Peon.h"


Peon::Peon(int speed, int armor, int damage, int health, int rangeAttack) :
Alliance(speed, armor, damage, health, rangeAttack) {

}

char Peon::getCharType() const {
    return 'P';
}



