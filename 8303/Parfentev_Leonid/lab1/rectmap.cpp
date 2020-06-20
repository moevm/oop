#include "rectmap.hpp"


bool
RectMapIter::valid() const
{
    return x() >= 0
        && x() < _map->width()
        && y() >= 0
        && y() < _map->height();
}

Cell &
RectMapIter::cell() const
{
    return _map->at(point());
}

// Vec2
// RectMapIter::delta(const RectMapIter &o) const
// {
//     return o.point().delta(point());
// }

void
RectMapIter::moveTo(Vec2 xy)
{
    _pt = xy;
}

RectMapIter
RectMapIter::otherAt(Vec2 xy) const
{
    RectMapIter other = *this;
    other.moveTo(xy);
    return other;
}

void
RectMapIter::advance(int d)
{
    int nx = x() + d,
        w = _map->width();
    _pt = Vec2{nx % w, y() + nx / w};
}

RectMapIter
RectMapIter::advanced(int d) const
{
    RectMapIter other = *this;
    other.advance(d);
    return other;
}
