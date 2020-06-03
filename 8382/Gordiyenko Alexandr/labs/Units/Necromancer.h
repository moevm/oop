#ifndef LABS_NECROMANCER_H
#define LABS_NECROMANCER_H

#include "Magic.h"

class Necromancer : public Magic {
public:

    Necromancer(int x, int y){
        this->x=x;
        this->y = y;
        this->param.health=320;
        this->param.armor=170;
        this->param.damage = 170;
        this->param.mana = 1160;
    }
    char type() {return 'N';}
};

#endif //LABS_NECROMANCER_H
