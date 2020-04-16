#ifndef ITERATOR_H
#define ITERATOR_H
#include "field.h"
#include "units.h"

class Iterator
{
    const Field* field;
    Unit* currUnit;
    int x;
    int y;
    bool isFirstIter;
public:
    Iterator(Field* field);
    void Next();
    Iterator& operator++(int);
    Unit*& operator*();
    bool canFindNext();
    void getXY();
    bool operator!= (const Iterator& iter) {return currUnit!=iter.currUnit;}

};


#endif // ITERATOR_H
