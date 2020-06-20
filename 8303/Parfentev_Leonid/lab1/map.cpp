#include "point.hpp"
#include "unit.hpp"
#include "map.hpp"


MapIter
Map::addUnit(Unit *u, Vec2 pt)
{
    if (u->hasPosition())
        return MapIter::makeNull();

    if (_units_max >= 0
        && _units_count == _units_max)
        return MapIter::makeNull();

    RectMapIter rmiter = _rm.iterAt(pt);
    Cell &cell = rmiter.cell();

    if (cell.placeable())
        return MapIter::makeNull();

    cell.setPlaceable(u);
    u->setPosition(pt);

    ++_units_count;

    return MapIter{rmiter};
}

Unit *
Map::removeUnitAt(Vec2 at)
{
    RectMapIter rmiter = _rm.iterAt(at);
    Cell &cell = rmiter.cell();
    Unit *u = dynamic_cast<Unit *>(cell.placeable());

    if (u) {
        --_units_count;
        cell.setPlaceable(nullptr);
        u->unsetPosition();
    }

    return u;
}

Unit *
MapIter::unit() const
{
    return dynamic_cast<Unit *>(_it.cell().placeable());
}
