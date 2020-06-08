//
// Created by therealyou on 11.02.2020.
//

#include "Goblin.h"

Goblin::Goblin(int speed, int armor, int damage, int health, int rangeAttack) :
Orcs(speed, armor, damage, health, rangeAttack) {

}

char Goblin::getCharType() const {
    return 'G';
}
