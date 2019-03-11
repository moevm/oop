#include "RegularPentagon.h"
#include <cmath>
long RegularPentagon::ID = 0;
void RegularPentagon::move(vector<Points> point) {
    if (point.size() > 1) {
        throw invalid_argument("Only Center Point");
    }
    _center.x = point[0].x;
    _center.y = point[0].y;
}

void RegularPentagon::rotate(int angle) {
    double x = _center.x;
    double y = _center.y;
    _center.x = (x * cos(angle) - y * sin(angle));
    _center.y = (y * cos(angle) + x * sin(angle));
}

void RegularPentagon::scale(int coeff) {
    if (coeff <= 0) {
        throw invalid_argument("Coefficient <= 0");
    }
    _radius *= coeff;
}

void RegularPentagon::set_color(string new_color) {
    this->color = new_color;
}

string RegularPentagon::get_color() {
    return this->color;
}


std::ostream &operator<<(std::ostream &os, const RegularPentagon &regPent) {
    os << "Regular Pentagon center points: " << endl;
    os << "(" << regPent._center.x << ";" << regPent._center.y << ")" << endl;
    os << "Regular Pentagon radius: " << endl;
    os << "(" << regPent._radius << ")" << endl;
    os << "Regular Pentagon color: " << regPent.color << endl;
    os << "Regular Pentagon ID:" << regPent.id << endl;
    return os;
}

