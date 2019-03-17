#pragma once

#include <iostream>
#include "shape.h"
#include <vector>

using namespace std;

class Square : public Shape {
private:
    static long ID;
    int NUMBER_POINTS = 4;
public:
    long  id;
    vector<Points> _points;
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
    int get_number_points() const;
    ~Square() {
        ID--;
    }
};
std::ostream &operator<<(std::ostream &os, const Square &square);