//
// Created by anton on 27.02.2020.
//

#include "Necromancer.h"
Necromancer::Necromancer(){
    health = 100;
    armor = 25;
    attack = 10;
    attackRange = 5;
}
char Necromancer::getClass() const {
    return 'N';
}