#ifndef LABS_KATANA_DUDE_H
#define LABS_KATANA_DUDE_H

#include "Melee.h"

class Katana : public Melee {
public:
    char type() {
        return 'K';
    }

    Katana(int x, int y){
        this->x=x;
        this->y = y;
        this->param.health=120;
        this->param.armor=95;
        this->param.damage = 33;
    }
};

#endif //LABS_KATANA_DUDE_H
