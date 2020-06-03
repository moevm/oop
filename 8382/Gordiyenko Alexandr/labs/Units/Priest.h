#ifndef LABS_PRIEST_H
#define LABS_PRIEST_H

#include "Magic.h"

class Priest : public Magic {
public:
    char type() {
        return 'P';
    }

    Priest(int x, int y){
        this->x=x;
        this->y = y;
        this->param.health=220;
        this->param.armor=150;
        this->param.damage = 60;
        this->param.mana = 60;
    }
};

#endif //LABS_PRIEST_H
