#ifndef ITERATOR_H
#define ITERATOR_H

#include "Field.h"
#include "Unit/Unit.h"

class Iterator
{
    Field* field;
public:
    int x, y;
    bool isfind = false;
    Cell* cell;

    Iterator(Field* field);

    Cell*& operator*() {
        return cell;
    }

     bool operator!= (const Iterator& iter);

     bool goNext();
};

#endif // ITERATOR_H

