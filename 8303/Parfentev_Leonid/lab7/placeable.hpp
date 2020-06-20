#ifndef _H_PLACEABLE_HPP
#define _H_PLACEABLE_HPP

#include "point.hpp"

class Placeable {
    bool _placed = false;
    Vec2 _pos;

public:
    bool
    hasPosition() const { return _placed; }

    const Vec2 &
    position() const
    {
        return _pos;
    }

    void
    setPosition(const Vec2 &pos)
    {
        _pos = pos;
        _placed = true;
    }

    void
    unsetPosition()
    {
        _placed = false;
    }

    virtual ~Placeable() {}
};

#endif
