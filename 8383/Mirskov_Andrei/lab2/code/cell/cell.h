//
// Created by andrei on 04.04.2020.
//

#ifndef OOP_LAB2_CELL_H
#define OOP_LAB2_CELL_H


#include "../landscape/landscape.h"
#include "../landscape/ground.h"
#include "../landscape/liquid.h"
#include "../landscape/wall.h"
#include "../base/base.h"

class Cell {
public:
    Cell();

    Landscape* getLandscape();

    Unit* getUnit();

    Neutral* getNeutral();

    Base* getBase();

    void setUnit(Unit*);

    void setNeutral(Neutral*);

    void setBase(Base*);

    bool isUnit();

    bool isNeutral();

    bool isBase();
private:
    Landscape* landscape = nullptr;

    Unit* unit = nullptr;

    Neutral* neutral = nullptr;

    Base* base = nullptr;
};


#endif //OOP_LAB2_CELL_H
