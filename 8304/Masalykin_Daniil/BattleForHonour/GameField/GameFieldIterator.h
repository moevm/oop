#ifndef BATTLEFORHONOUR_GAMEFIELDITERATOR_H
#define BATTLEFORHONOUR_GAMEFIELDITERATOR_H


#include <iterator>
#include "Point.h"
#include "FieldCell.h"

class GameFieldIterator: public std::iterator<std::input_iterator_tag, FieldCell>{

    friend class GameField;

private:

    Point point;
    const Point cpoint;
    FieldCell **field;
    const int fieldHeight;
    const int fieldWidth;

    GameFieldIterator(const Point p, FieldCell **field, const int fieldHeight, const int fieldWidth):
            point(p),
            cpoint(p),
            field(field),
            fieldWidth(fieldWidth),
            fieldHeight(fieldHeight){};

public:

    GameFieldIterator(const GameFieldIterator &it):
            point(it.point),
            field(it.field),
            fieldWidth(it.fieldWidth),
            fieldHeight(it.fieldHeight){};

    bool operator!=(const GameFieldIterator &sub) {
        return cpoint != sub.point;
    };
    bool operator==(const GameFieldIterator &sub) {
        return cpoint == sub.point;
    };
    typename GameFieldIterator::reference operator*() {
        return  field[point.y][point.x];
    };

    GameFieldIterator&  operator++() {

        Point next = point;
        next.x++;

        if (next.x < fieldWidth) {
            point = next;

            return *this;
        } else{
            next.x = 0;
            next.y++;
            point = next;

            return *this;
        }

    };


};


#endif //BATTLEFORHONOUR_GAMEFIELDITERATOR_H
