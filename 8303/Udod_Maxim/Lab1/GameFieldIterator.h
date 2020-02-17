//
// Created by shenk on 16.02.2020.
//

#ifndef UNTITLED13_GAMEFIELDITERATOR_H
#define UNTITLED13_GAMEFIELDITERATOR_H

#include <iterator>
#include "Point.h"
#include "Units/Unit.h"

class GameFieldIterator: public std::iterator<std::input_iterator_tag, Unit*>{

    friend class GameField;

private:

    Point p;
    Unit ***field;
    int fieldHeight;
    int fieldWidth;

    GameFieldIterator(Point p, Unit *** field, int fieldHeight, int fieldWidth): p(p){

        this->p = p;
        this->field = field;
        this->fieldHeight = fieldHeight;
        this->fieldWidth = fieldWidth;

    };

public:

    GameFieldIterator(const GameFieldIterator &it): p(it.p){

        p = it.p;
        field = it.field;
        fieldHeight = it.fieldHeight;
        fieldWidth = it.fieldWidth;

    };

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

#endif //UNTITLED13_GAMEFIELDITERATOR_H
