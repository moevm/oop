#include <iostream>
#include <vector>
#include "Ellipse.h"
#include <cmath>

using namespace std;
long Ellipse::ID = 0;
void Ellipse::move(vector<Points> point) {
    if (point.size() > 1) {
        throw invalid_argument("Only Center Point");
    }
    _points.x = point[0].x;
    _points.y = point[0].y;
}

void Ellipse::rotate(int angle) {
    double x = _points.x;
    double y = _points.y;
    _points.x = x + (x * cos(angle)+ y * sin(angle));
    _points.y = y - (y * cos(angle) + x * sin(angle));
}

void Ellipse::scale(int coeff) {
    if (coeff <= 0) {
        throw invalid_argument("Coefficient <= 0");
    }
    _xradius *= coeff;
    _yradius *= coeff;
}

void Ellipse::set_color(string new_color) {
    this->color = new_color;
}

string Ellipse::get_color() {
    return this->color;
}

std::ostream &operator<<(std::ostream &os, const Ellipse &ellipse) {
    os << "Ellipse center points: " << endl;
    os << "(" << ellipse._points.x << ";" << ellipse._points.y << ")" << endl;
    os << "Ellipse xradius and yradius: " << endl;
    os << "(" << ellipse._xradius << ";" << ellipse._yradius << ")" << endl;
    os << "Ellipse color: " << ellipse.color << endl;
    os << "Ellipse ID:" << ellipse.id << endl;
    return os;
}
