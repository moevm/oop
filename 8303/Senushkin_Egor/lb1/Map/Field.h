//
// Created by egor on 15.03.2020.
//

#ifndef OOP_LB1__2_FIELD_H
#define OOP_LB1__2_FIELD_H


#include "../Unit/Unit.h"
#include "Point.h"
#include <iostream>

#include "FieldIterator.h"


class Field {
    //friend class Unit;

private:
    //class FieldIterator;
    Unit*** map;
    int height, width;
    int maxUnit = 10;

    void print_type(Point p) const;

public:
    explicit Field(int size);
    Field(int x, int y);
    Field(const Field& other);
    Field(Field&& other);
    Field& operator=(const Field& other);
    Field& operator=(Field&& other);

    void addObject(Unit* object, int x, int y);

    void deleteObject(int x, int y);
    void deleteObject(Point& p);
    void deleteObject(Unit* object);

    void moveObject(Point p1, Point p2);
    void moveObject(Unit* object, Point p1);

    Unit * getObject(Point& p) const;
    int getHeight() const;
    int getWidth() const;

    typedef FieldIterator iterator;
    typedef FieldIterator const_iterator;

    iterator begin() { return FieldIterator(Point(0, 0), map, height, width); }
    iterator end() { return FieldIterator(Point(0, height), map, height, width); }
/*
    const_iterator begin() const;
    const_iterator end() const;
    */

    void print() const;


    ~Field();

};


#endif //OOP_LB1__2_FIELD_H
