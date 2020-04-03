//
// Created by mensch on 11.03.2020.
//

#include "Knight.h"

Knight::Knight() {
    health = 150;
    damage = 30;
    armor = 10;
}

Texture Knight::texture() const{
    return KNIGHT;
}

