#ifndef ITERATOR_H
#define ITERATOR_H

#include "Field.h"
#include "Unit/Unit.h"

class Iterator
{
    Field field;
public:
    int x, y;
    bool isfind = false;
    Unit* cur;

    Iterator(Field &field);

    Unit*& operator*() {
        return cur;
    }

     //Unit*& operator++ ();

     bool operator!= (const Iterator& iter);
     //bool operator== (const Iterator& iter);

     bool goNext();
     Iterator end();
};

#endif // ITERATOR_H

