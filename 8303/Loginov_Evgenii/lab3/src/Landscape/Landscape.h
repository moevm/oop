//
// Created by Evgeniy on 3/10/2020.
//

#ifndef OOP1_3_LANDSCAPE_H
#define OOP1_3_LANDSCAPE_H

#include "../Unit/Unit.h"
#include "../Unit/UnitCreater.h"

class Landscape {
public:
    virtual bool canMove(Unit *unit) = 0;
    virtual char typeLandscape() = 0;

    virtual ~Landscape() {}
};


#endif //OOP1_3_LANDSCAPE_H
