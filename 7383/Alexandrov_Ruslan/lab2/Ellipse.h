#pragma once

#include <iostream>
#include <vector>
#include "shape.h"

using namespace std;

class Ellipse : public Shape {
public:
    Points _points;
    int _xradius;
    int _yradius;
    long  id;
    static long ID;
    Ellipse(Points center, int xradius, int yradius) : id(ID++) {
        if (xradius <= 0 || yradius <= 0) {
            throw invalid_argument("Radius <= 0");
        }
        _points = center;
        _xradius = xradius;
        _yradius = yradius;
    }

    void move(vector<Points> point) override;

    void rotate(int angle) override;

    void scale(int coeff) override;

    void set_color(string new_color) override;
    string get_color() override;
};

std::ostream &operator<<(std::ostream &os, const Ellipse &square);