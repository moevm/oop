#include "BasePoint.h"

BasePoint::BasePoint(int x_, int y_) : x(x_), y(y_) { }

BasePoint::BasePoint(const BasePoint& point) : x(point.x), y(point.y) { }

BasePoint& BasePoint::operator= (const BasePoint& point) {
    if (&point == this)
        return *this;

    x = point.x;
    y = point.y;

    return *this;
}

BasePoint::BasePoint(BasePoint&& point) noexcept : x(point.x), y(point.y) { }

BasePoint& BasePoint::operator= (BasePoint&& point) noexcept {
    if (&point == this)
        return *this;

    x = point.x;
    y = point.y;

    return *this;
};

std::string BasePoint::getDescription() const {
    std::string res{};
    res.append("Base point:");
    res.append("\n\tCoords: " + std::to_string(x) + ";" + std::to_string(y));

    return res;
}

eFIGURE BasePoint::getType() const {
    return POINT;
}

float BasePoint::getX() {
    return x;
}

float BasePoint::getY() {
    return y;
}

void BasePoint::setX(float x_) {
    x = x_;
}

void BasePoint::setY(float y_) {
    y = y_;
}
