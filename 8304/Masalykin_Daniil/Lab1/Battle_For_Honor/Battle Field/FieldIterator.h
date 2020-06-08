//
// Created by anton on 02.03.2020.
//

#ifndef BATTLE_FOR_HONOR_FIELDITERATOR_H
#define BATTLE_FOR_HONOR_FIELDITERATOR_H

#include "Field.h"

class FieldIterator {

public:
    FieldIterator(Field *field);

    bool isActive();

    Cell *operator->();

    Cell *operator++();

private:
    bool active;
    Field *field;
    unsigned curWidth;
    unsigned curHeight;
};

#endif //BATTLE_FOR_HONOR_FIELDITERATOR_H
