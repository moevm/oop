#include <stdexcept>
#include <iterator>

#include <assert.h>

#include "game.hpp"


void
GameMap::destroy()
{
    delete[] _map;
    _cur_units = _max_units = 0;
}

void
GameMap::copy_from(const GameMap &m)
{
    _w = m._w;
    _h = m._h;
    _map = new GameCell[_w * _h];
    _max_units = m._max_units;
    _cur_units = m._cur_units;

    std::copy(m.begin(), m.end(), begin());
}

void
GameMap::throw_units_count()
{
    throw std::runtime_error{
        "Maximum unit count exceeded"};
}

void
GameMap::setMaxUnitsCount(int n)
{
    if (n > 0
        && n < _cur_units)
        throw_units_count();
    _max_units = n;
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
        throw_units_count();

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
