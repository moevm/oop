#ifndef _H_RECTMAP_HPP
#define _H_RECTMAP_HPP

#include "point.hpp"
#include "placeable.hpp"
#include "landscape.hpp"


class Unit;

class Cell {
    Landscape *_l = nullptr;
    Unit *_u = nullptr;
    Placeable *_obj = nullptr;

public:
    Cell() {}

    ~Cell();

    Landscape *landscape() const { return _l; }
    void setLandscape(Landscape *l)
    {
        delete _l;
        _l = l;
    }

    Unit *unit() const { return _u; }
    void setUnit(Unit *u) { _u = u; }

    Placeable *object() const { return _obj; }
    void setObject(Placeable *p) { _obj = p; }
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
    const Cell &at(Vec2 pt) const
    {
        return _storage[pt.x() + pt.y()*_w];
    }
    RectMapIter iterAt(Vec2 pt) { return RectMapIter{this, pt}; }

    ~RectMap()
    {
        delete[] _storage;
    }
};

#endif
