#ifndef LABS_SLINGERMAN_H
#define LABS_SLINGERMAN_H

#include "Range.h"

class Slingerman : public Range {
public:
    char type() {
        return 'S';
    }
    Slingerman(int x, int y){
        this->x=x;
        this->y = y;
        this->param.health=150;
        this->param.armor=100;
        this->param.damage = 30;
    }
};

#endif //LABS_SLINGERMAN_H
