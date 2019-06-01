#pragma once

#include <iostream>
#include <vector>
#include "shape.h"

using namespace std;

class Ellipse : public Shape {
private:
    static long ID;
    int NUMBER_POINTS = 1;
public:
    long  id;
    int _xradius;
    int _yradius;
    Points _center;
    Ellipse(vector<Points> center, int xradius, int yradius) : id(ID++) {
        if (center.size() != NUMBER_POINTS || xradius <= 0 || yradius <= 0) {
            throw invalid_argument("Incorrect input");
        }
        this->_center.x = center[0].x;
        this->_center.y = center[0].y;
        _xradius = xradius;
        _yradius = yradius;
    }
    void move(vector<Points> point) override;

    void rotate(int angle) override;

    void scale(int coeff) override;

    void set_color(string new_color) override;
    string get_color() override;
    ~Ellipse() {
        ID--;
    }
};

std::ostream &operator<<(std::ostream &os, const Ellipse &square);