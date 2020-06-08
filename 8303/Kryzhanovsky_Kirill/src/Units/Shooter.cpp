//
// Created by therealyou on 11.02.2020.
//

#include "Shooter.h"


Shooter::Shooter(int speed, int armor, int damage, int health, int rangeAttack) :
Alliance(speed, armor, damage, health, rangeAttack) {

}

char Shooter::getCharType() const {
    return 'S';
}
