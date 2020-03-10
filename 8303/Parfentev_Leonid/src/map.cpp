#include <vector>
#include <queue>
#include <stdexcept>
#include <iterator>

#include <assert.h>

#include "map.hpp"
#include "unit.hpp"


GameCell::~GameCell()
{
    delete _unit;
    _unit = nullptr;
}




bool
Point::operator==(const Point &pt) const
{
    return _x == pt._x
        && _y == pt._y;
}

double
Point::distance(const Point &pt) const
{
    int dx = _x - pt._x,
        dy = _y - pt._y;
    return sqrt(dx*dx + dy*dy);
}

bool
Point::adjacent(const Point &pt) const
{
    return abs(_x - pt._x) == 1
        || abs(_y - pt._y) == 1;
}



void
GameMap::destroy()
{
    delete[] _map;
    _cur_units = _max_units = 0;
}

bool
GameMap::setMaxUnitsCount(int n)
{
    if (n > 0
        && n < _cur_units)
        return false;

    _max_units = n;
    return true;
}

int
GameMap::cellIndex(const Point &pt) const
{
    assert(ptValid(pt));

    return pt.x() + pt.y() * _w;
}

GameCell &
GameMap::at(const Point &pt)
{
    return _map[cellIndex(pt)];
}

const GameCell &
GameMap::at(const Point &pt) const
{
    return _map[cellIndex(pt)];
}

MapIter
GameMap::iterAt(const Point &pt)
{
    return {this, pt};
}

MapConstIter
GameMap::iterAt(const Point &pt) const
{
    return {this, pt};
}

bool
GameMap::ptValid(const Point &pt) const
{
    int x = pt.x(),
        y = pt.y();

    return (x >= 0 && x < _w)
        && (y >= 0 && y < _h);
}

bool
GameMap::pathExists(const Point &src,
                    const Point &dest,
                    int max_length) const
{
    assert(ptValid(src));
    assert(ptValid(dest));

    struct Pt2 {
        Point pt;
        int depth;

        Pt2(const Point &pt, int depth=0)
            :pt{pt}, depth{depth} {}

        Pt2 toDirection(int dir) const
        {
            assert(dir >= 0 && dir < 8);

            int d1 = (dir + 1) % 8;
            int dx = (d1 % 4 == 3) ? 0 : (d1 < 4) ? 1 : -1,
                dy = (dir % 4 == 0) ? 0 : (dir < 4) ? 1 : -1;

            return Pt2{pt.shifted(dx, dy), depth + 1};
        }

        int index(const GameMap *m) const
        {
            return m->cellIndex(pt);
        }

        bool operator==(const Point &pt2)
        {
            return pt == pt2;
        }
    };

    std::vector<bool> visited (area(), false);
    std::queue<Pt2> frontier {{src}};

    while (!frontier.empty()) {
        Pt2 current = frontier.front();
        frontier.pop();

        if (current == dest)
            return true;

        if (max_length >= 0
            && current.depth >= max_length)
            continue;

        visited[current.index(this)] = true;

        for (int i = 0; i < 8; ++i) {
            Pt2 shifted = current.toDirection(i);
            if (!ptValid(shifted.pt))
                continue;

            if (visited[shifted.index(this)])
                continue;

            if (at(shifted.pt).unit())
                continue;

            frontier.push(shifted);
        }
    }

    return false;
}

bool
GameMap::placeUnit(const Point &pt,
                   BaseUnit *u)
{
    GameCell &cell = at(pt);
    if (cell.unit())
        return false;

    if (_max_units > 0
        && _cur_units >= _max_units)
        return false;

    cell.setUnit(u);
    u->setPoint(pt);
    _cur_units++;

    return true;
}

BaseUnit *
GameMap::removeFrom(const Point &pt)
{
    GameCell &cell = at(pt);
    BaseUnit *u = cell.unit();

    if (!u)
        return nullptr;

    cell.setUnit(nullptr);
    u->unsetPoint();
    return u;
}
