#pragma once
#include <iostream>
#include "shape.h"
#include <vector>

class RegularPentagon : public  Shape {
private:
    static long ID;
    int NUMBER_POINTS = 1;
public:
    int _radius;
    long  id;
    Points _center;
    RegularPentagon(vector<Points> center, int radius) : id(ID++) {
        if (center.size() != NUMBER_POINTS || radius <= 0) {
            throw invalid_argument("Incorrect input");
        }
        _center.x = center[0].x;
        _center.y = center[0].y;
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