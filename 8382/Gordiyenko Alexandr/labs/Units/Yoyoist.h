//
// Created by alexg on 03.06.2020.
//

#ifndef LABS_YOYOIST_H
#define LABS_YOYOIST_H

#include "Melee.h"

class Yoyoist: public Melee {
public:
    char type() {return 'Y';}
    Yoyoist(int x, int y){
        this->x=x;
        this->y = y;
        this->param.health=120;
        this->param.armor=64;
        this->param.damage = 25;
    }
};

#endif //LABS_Yoyoist_H
