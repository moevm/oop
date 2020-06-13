//
// Created by anton on 27.02.2020.
//

#include "Flamen.h"
Flamen::Flamen(){
    health = 125;
    armor = 0;
    attack = 15;
    attackRange = 5;
}
char Flamen::getClass() const {
    return 'F';
}