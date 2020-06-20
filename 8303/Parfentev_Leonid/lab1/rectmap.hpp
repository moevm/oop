#ifndef _H_RECTMAP_HPP
#define _H_RECTMAP_HPP

#include "point.hpp"
#include "placeable.hpp"


class Cell {
    Placeable *_p = nullptr;

public:
    Cell() {}

    ~Cell()
    {
        delete _p;
    }

    Placeable *placeable() const { return _p; }
    void setPlaceable(Placeable *p) { _p = p; }
};

class RectMap;

class RectMapIter {
    RectMap *_map;
    Vec2 _pt;

public:
    RectMapIter(RectMap *map, Vec2 pt)
        :_map{map}, _pt{pt} {}
    RectMapIter(RectMap *map, int x, int y)
        :_map{map}, _pt{x, y} {}

    static RectMapIter makeNull() { return {nullptr, {0, 0}}; }

    bool operator==(const RectMapIter &o) const
    {
        return _map == o._map
            && _pt == o._pt;
    }
    bool operator!=(const RectMapIter &o) const
    {
        return !(*this == o);
    }

    int x() const { return _pt.x(); }
    int y() const { return _pt.y(); }
    Vec2 point() const { return _pt; }

    Cell &cell() const;

    bool null() const { return _map == nullptr; }
    bool valid() const;

    // Vec2 delta(const RectMapIter &o) const;

    void moveTo(Vec2 xy);
    RectMapIter otherAt(Vec2 xy) const;

    void advance(int d);
    RectMapIter advanced(int d) const;
};

class RectMap {
    const int _w, _h;
    Cell * const _storage;

public:
    RectMap(int w, int h)
        :_w{w}, _h{h}, _storage{new Cell [w * h]} {}

    int width() const { return _w; }
    int height() const { return _h; }

    Cell &at(Vec2 pt) { return _storage[pt.x() + pt.y()*_w]; }
    RectMapIter iterAt(Vec2 pt) { return RectMapIter{this, pt}; }

    ~RectMap()
    {
        delete[] _storage;
    }
};

#endif
