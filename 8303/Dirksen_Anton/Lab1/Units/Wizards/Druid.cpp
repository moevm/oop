//
// Created by mensch on 11.03.2020.
//

#include "Druid.h"

Druid::Druid(){
    health = 60;
    damage = 20;
    mana = 60;
}

Texture Druid::texture() const{
    return DRUID;
}