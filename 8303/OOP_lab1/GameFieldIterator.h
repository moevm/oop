#ifndef OOP_LAB1_GAMEFIELDITERATOR_H
#define OOP_LAB1_GAMEFIELDITERATOR_H

#include <iterator>
#include "Point.h"
#include "Unit.h"

class GameFieldIterator: public std::iterator<std::input_iterator_tag, Unit*>{

    friend class GameField;

private:

    Point p;
    Unit ***field;
    const int fieldHeight;
    const int fieldWidth;

    GameFieldIterator(const Point p, Unit *** field, const int fieldHeight,const  int fieldWidth):

        p(p),
        field(field),
        fieldHeight(fieldHeight),
        fieldWidth(fieldWidth){}

    ;

public:

    GameFieldIterator(const GameFieldIterator &it):

        p (it.p),
        field (it.field),
        fieldHeight(it.fieldHeight),
        fieldWidth (it.fieldWidth){}

    ;

    bool operator!=(const GameFieldIterator &other) { return p != other.p; };
    bool operator==(const GameFieldIterator &other) { return p == other.p; };
    typename GameFieldIterator::reference operator*() { return  field[p.y][p.x]; };

    GameFieldIterator&  operator++() {

        Point next = p;
        next.x++;

        if (next.x < fieldWidth) {
            p = next;
            return *this;
        } else{

            next.x = 0;
            next.y++;

            p = next;
            return *this;
        }

    };


};

#endif //OOP_lab1_GAMEFIELDITERATOR_H