//
// Created by mensch on 02.03.2020.
//

#include "Bowman.h"

Bowman::Bowman(){
    health = 70;
    damage = 10;
    range = 5;
}

Texture Bowman::texture() const{
    return BOWMAN;
}