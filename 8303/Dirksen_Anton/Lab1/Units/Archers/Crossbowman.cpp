//
// Created by mensch on 02.03.2020.
//

#include "Crossbowman.h"


Crossbowman::Crossbowman(){
    health = 60;
    damage = 20;
    range = 8;
}

Texture Crossbowman::texture() const{
    return CROSSBOWMAN;
}