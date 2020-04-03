//
// Created by mensch on 11.03.2020.
//

#include "Squire.h"

Squire::Squire() {
    health = 100;
    damage = 20;
    armor = 5;
}

Texture Squire::texture() const{
    return SQUIRE;
}