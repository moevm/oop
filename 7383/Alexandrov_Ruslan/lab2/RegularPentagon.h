#pragma once
#include <iostream>
#include "shape.h"
#include <vector>

class RegularPentagon : public  Shape {
public:
    Points _center;
    int _radius;
    long  id;
    static long ID;
    RegularPentagon(Points center, int radius) : id(ID++) {
        if (radius <= 0) {
            throw invalid_argument("Radius <= 0");
        }
        _center = center;
        _radius = radius;
    }
    void move(vector<Points> point) override;
    void  rotate(int angle) override;
    void  scale(int coeff) override;
    void  set_color(string new_color) override;
    string  get_color() override;
};

std::ostream &operator<<(std::ostream &os, const RegularPentagon &square);