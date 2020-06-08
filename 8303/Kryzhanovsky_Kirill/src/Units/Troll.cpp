//
// Created by therealyou on 11.02.2020.
//

#include "Troll.h"

Troll::Troll(int speed, int armor, int damage, int health, int rangeAttack) :
Orcs(speed, armor, damage, health, rangeAttack) {

}

char Troll::getCharType() const {
    return 'T';
}
