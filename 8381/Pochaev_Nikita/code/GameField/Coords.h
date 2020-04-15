#ifndef OOP_COORDS_H
#define OOP_COORDS_H

#include <cstddef>

struct Coords
{
    Coords() : x(0), y(0) { }
    Coords(size_t x_, size_t y_) : x(x_), y(y_) { }
    size_t x{};
    size_t y{};

    bool operator== (const Coords &o)
    {
        return x == o.x && y == o.y;
    }

    bool operator< (const Coords &o) const
    {
        return x < o.x || (x == o.x && y < o.y);
    }
};

#endif //OOP_COORDS_H
