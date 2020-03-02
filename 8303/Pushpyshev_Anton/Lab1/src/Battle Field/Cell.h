#ifndef BATTLE_FOR_HONOR_CELL_H
#define BATTLE_FOR_HONOR_CELL_H

#include "../Units/Unit.h"

class Cell {
public:
    bool is_full;
    Unit* unit;
        Cell(){
            is_full = false;
            unit = nullptr;
        }


};


#endif //BATTLE_FOR_HONOR_CELL_H
