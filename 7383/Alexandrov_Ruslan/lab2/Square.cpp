#include "Square.h"
#include <cmath>
long Square::ID = 0;

void Square::move(vector<Points> points) {
    for (int i = 0; i < NUMBER_POINTS; i++) {
        _points[i].x = points[i].x;
        _points[i].y = points[i].y;
    }
}

void Square::rotate(int angle) {
    for (int i = 0; i < NUMBER_POINTS; i++) {
        double x = _points[i].x;
        double y = _points[i].y;
        _points[i].x = (x * cos(angle) - y * sin(angle));
        _points[i].y = (y * cos(angle) + x * sin(angle));
    }
}

void Square::scale(int coeff) {
    if (coeff <= 0) {
        throw invalid_argument("Coefficient <= 0");
    }
    double x_first = _points[0].x;
    double y_first = _points[0].y;
    for (int i = 1; i < NUMBER_POINTS; i++) {
        double x_side = _points[i].x - x_first;
        double y_side = _points[i].y - y_first;
        x_side *= coeff;
        y_side *= coeff;
        _points[i].x = x_first + x_side ;
        _points[i].y =  y_first + y_side ;
    }
}

void Square::set_color(string new_color) {
    this->color = new_color;
}

string Square::get_color() {
    return this->color;
}

std::ostream &operator<<(std::ostream &os, const Square &square) {
    os << "Square points: " << endl;
    for (int i = 0; i < square.NUMBER_POINTS; i++) {
        os << "(" << square._points[i].x << ";" << square._points[i].y << ")" << endl;
    }
    os << "Square color: " << square.color << endl;
    os << "Square ID:" << square.id << endl;
    return os;
}

