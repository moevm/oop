//
// Created by egor on 26.03.2020.
//

#ifndef OOP_LB1__2_FIELDITERATOR_H
#define OOP_LB1__2_FIELDITERATOR_H


#include "../Unit/Unit.h"
#include "Point.h"
#include <iterator>


class FieldIterator : public std::iterator<std::input_iterator_tag, Unit*>{
    friend class Field;

private:
    Point coordinates;
    Unit*** field;
    int height, width;

private:
    FieldIterator(const Point& coordinates, Unit*** field, int height, int width)
    {
        this->coordinates = coordinates;
        this->field = field;
        this->height = height;
        this->width = width;
    }

public:
    FieldIterator(const FieldIterator& it)
    {
        coordinates = it.coordinates;
        field = it.field;
        height = it.height;
        width = it.width;
    }

    bool operator!=( const FieldIterator& other) const
    {
        return coordinates != other.coordinates;
    }

    bool operator==(const FieldIterator& other) const
    {
        return coordinates == other.coordinates;
    }


    reference operator*()const
    {
        return field[coordinates.y][coordinates.x];
    }


    FieldIterator& operator++()
    {
        Point next = coordinates;
        next.x++;

        if (next.x < width) {
            coordinates = next;
            return *this;
        } else{

            next.x = 0;
            next.y++;

            coordinates = next;
            return *this;
        }
    }


};


#endif //OOP_LB1__2_FIELDITERATOR_H
