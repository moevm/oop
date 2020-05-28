#ifndef BASE_H
#define BASE_H
#include <iostream>
#include <vector>
#include <set>
#include "LandScape.h"
#endif //BASE_H

struct Component{
    virtual void SayHi() = 0;
};

struct Node: Component{
    void SayHi() override;
    Point me;
};

struct Composite:Component{
    void SayHi() override;
    std::set<Point> components;
};

struct Base {
    explicit Base(int a = 5);
    Composite Units;
    void addUnit(Point const& a);
    void removeUnit(Point const& a);
    int count;
    int max_count;
    int Hp;
};