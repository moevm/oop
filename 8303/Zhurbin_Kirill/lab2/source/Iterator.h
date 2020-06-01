#ifndef OOP1_ITERATOR_H
#define OOP1_ITERATOR_H

#include "Unit.h"
#include "Field.h"

class Iterator{
    Field field;

public:
    int x, y;
    bool isFind = false;
    Unit* cur;

    Iterator(Field &field);
    Unit*& operator++ ();

    bool operator!= (const Iterator& iter);
    bool operator== (const Iterator& iter);
    Unit*& operator* ();


    Iterator end();

    bool hasNext();
};

#endif //OOP1_ITERATOR_H
