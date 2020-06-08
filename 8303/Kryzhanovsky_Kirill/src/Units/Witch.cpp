//
// Created by therealyou on 11.02.2020.
//

#include "Witch.h"


Witch::Witch(int speed, int armor, int damage, int health, int rangeAttack) :
Magicians(speed, armor, damage, health, rangeAttack) {

}

char Witch::getCharType() const {
    return 'W';
}
