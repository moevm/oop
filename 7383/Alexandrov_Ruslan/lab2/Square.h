#pragma once

#include <iostream>
#include "shape.h"
#include <vector>

using namespace std;

class Square : public Shape {
public:
    vector<Points> _points;
    int const NUMBER_POINTS = 4;
    long  id;
    static long ID;
    Square(vector<Points> &points) : id(ID++) {
        if (points.size() != NUMBER_POINTS) {
            throw invalid_argument("Square has 4 points");
        }
        _points = points;
    }

    void move(vector<Points> points) override;

    void rotate(int angle) override;

    void scale(int coeff) override;

    void set_color(string new_color) override;

    string get_color() override;
};
std::ostream &operator<<(std::ostream &os, const Square &square);