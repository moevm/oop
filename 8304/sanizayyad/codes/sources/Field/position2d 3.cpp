#include "position2d.hpp"

Position2D::Position2D(int x, int y)
{
    this->x = x;
    this->y = y;
}


Position2D::Position2D(const Position2D& point)
{
    this->x = point.x;
    this->y = point.y;
}


Position2D::Position2D(Position2D&& point)
{
    this->x = point.x;
    this->y = point.y;
}


Position2D& Position2D::operator=(Position2D&& point)
{
    if (this == &point) {
        return *this;
    }

    this->x = point.x;
    this->y = point.y;

    return *this;
}


Position2D& Position2D::operator=(const Position2D& point)
{
    if (this == &point) {
        return *this;
    }

    this->x = point.x;
    this->y = point.y;

    return *this;
}
