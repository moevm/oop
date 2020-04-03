//
// Created by mensch on 11.03.2020.
//

#include "Archmage.h"

Archmage::Archmage(){
    health = 70;
    damage = 40;
    mana = 100;
}

Texture Archmage::texture() const{
    return ARCHMAGE;
}