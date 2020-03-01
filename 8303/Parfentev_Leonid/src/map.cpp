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
GamePos::valid() const
{
    return !null()
        && _x >= 0
        && _x < _map->width()
        && _y >= 0
        && _y < _map->height();
}

GameCell &
GamePos::cell() const
{
    return (*_map)(_x, _y);
}

bool
GamePos::operator==(const GamePos &pos) const
{
    return _map == pos._map
        && _x == pos._x
        && _y == pos._y;
}

bool
GamePos::adjacent(const GamePos &pos) const
{
    return _map == pos._map
        && (abs(_x - pos._x) == 1
            || abs(_y - pos._y) == 1);
}

bool
GamePos::pathExistsTo(const GamePos &pos, int max_length) const
{
    assert(valid());
    assert(pos.valid());
    if (_map != pos._map)
        return false;

    struct Pt2 {
        int x, y;
        int depth;

        Pt2(int x, int y, int d)
            :x{x}, y{y}, depth{d} {}

        Pt2(const GamePos &pos)
            :x{pos.x()}, y{pos.y()}, depth{0} {}

        Pt2 toDirection(int dir) const
        {
            assert(dir >= 0 && dir < 8);

            int d1 = (dir + 1) % 8;
            int dx = (d1 % 4 == 3) ? 0 : (d1 < 4) ? 1 : -1,
                dy = (dir % 4 == 0) ? 0 : (dir < 4) ? 1 : -1;

            return {x + dx, y + dy, depth + 1};
        }

        int index(const GameMap *m) const
        {
            return x + m->width() * y;
        }

        bool operator==(const GamePos &pos)
        {
            return x == pos.x() && y == pos.y();
        }
    };

    std::vector<bool> visited (_map->width() * _map->height(), false);
    std::queue<Pt2> frontier {{*this}};

    while (!frontier.empty()) {
        Pt2 pt = frontier.front();
        frontier.pop();

        if (pt == pos)
            return true;

        if (max_length >= 0
            && pt.depth >= max_length)
            continue;

        visited[pt.index(_map)] = true;

        for (int i = 0; i < 8; ++i) {
            Pt2 shifted = pt.toDirection(i);
            GamePos ipos {_map, shifted.x, shifted.y};
            if (!ipos.valid())
                continue;

            if (visited[shifted.index(_map)])
                continue;

            GameCell &icell = ipos.cell();
            if (icell.unit())
                continue;

            frontier.push(shifted);
        }
    }

    return false;

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

GameCell &
GameMap::operator()(int x, int y)
{
    assert((GamePos{this, x, y}.valid()));

    return _map[x + y * _w];
}

const GameCell &
GameMap::operator()(int x, int y) const
{
    assert((GamePos{this, x, y}.valid()));

    return _map[x + y * _w];
}

bool
GameMap::placeUnit(BaseUnit *u)
{
    GamePos pos = u->position();

    assert(pos.valid());
    assert(pos.map() == this);

    GameCell &cell = pos.cell();
    if (cell.unit())
        return false;

    if (_max_units > 0
        && _cur_units >= _max_units)
        return false;

    cell.setUnit(u);
    _cur_units++;
    return true;
}

void
GameMap::removeUnit(BaseUnit *u)
{
    GamePos pos = u->position();

    assert(pos.valid());
    assert(pos.map() == this);

    pos.cell().setUnit(nullptr);
    _cur_units--;
}
