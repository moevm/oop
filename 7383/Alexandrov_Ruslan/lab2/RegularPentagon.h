#pragma once
#include <iostream>
#include "Square.h"
#include <vector>

class RegularPentagon : public  Square {
    static long ID;
public:
    int _radius;
    long  id;
    Points _center;
    RegularPentagon(vector<Points> &points, int radius) : Square(points), id(ID++) {
        if (radius <= 0) {
            throw invalid_argument("Incorrect radius");
        }
        _center.x = points[0].x;
        _center.y = points[0].y;
        _radius = radius;
    }
    void move(vector<Points> point) override;
    void  rotate(int angle) override;
    void  scale(int coeff) override;
    void  set_color(string new_color) override;
    string  get_color() override;

    ~RegularPentagon() {
        ID--;
    }
};

std::ostream &operator<<(std::ostream &os, const RegularPentagon &square);