#ifndef _H_POINT_HPP
#define _H_POINT_HPP

class Vec2 {
    int _x, _y;

public:
    Vec2() :Vec2{0, 0} {}
    Vec2(int x, int y) :_x{x}, _y{y} {}

    int x() const { return _x; }
    int y() const { return _y; }

    bool operator==(const Vec2 &pt) const
    {
        return _x == pt._x && _y == pt._y;
    }
    bool operator!=(const Vec2 &pt) const
    {
        return !(*this == pt);
    }

    Vec2 delta(const Vec2 &o) const
    {
        return Vec2{_x - o._x, _y - o._y};
    }

    double length() const;
    double distance(const Vec2 &pt) const;

    bool unit() const;
    bool adjacent(const Vec2 &pt) const;

    Vec2 shifted(const Vec2 &dxy) const
    {
        return Vec2{_x + dxy._x, _y + dxy._y};
    }
};

#endif
