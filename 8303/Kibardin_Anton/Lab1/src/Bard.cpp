//
// Created by anton on 27.02.2020.
//

#include "Bard.h"
Bard::Bard(){
    health = 125;
    armor = 0;
    attack = 5;
    attackRange = 10;
}
char Bard::getClass() const {
    return 'B';
}