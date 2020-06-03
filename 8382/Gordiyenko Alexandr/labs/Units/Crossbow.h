#ifndef LABS_CROSSBOW_H
#define LABS_CROSSBOW_H

#include "Range.h"

class Crossbow : public Range {
public:
    char type() {return 'C';}
    Crossbow(int x, int y){
        this->x=x;
        this->y = y;
        this->param.health=90;
        this->param.armor=55;
        this->param.damage = 30;
    }
};

#endif //LABS_CROSSBOW_H
