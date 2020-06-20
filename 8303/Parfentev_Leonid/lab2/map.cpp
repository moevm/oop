#include "point.hpp"
#include "unit.hpp"
#include "placeable.hpp"
#include "base.hpp"
#include "neutral_object.hpp"
#include "landscape.hpp"
#include "map.hpp"


Map::Map(int w, int h)
    :_rm{w, h}
{
    for (auto rmiter = _rm.iterAt({0, 0});
         rmiter.y() < _rm.height();
         rmiter.advance(1)) {
        rmiter.cell().setLandscape(new landscapes::Normal {});
    }
}

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

    if (cell.unit())
        return MapIter::makeNull();

    cell.setUnit(u);
    u->setPosition(pt);

    ++_units_count;

    cell.landscape()->onEnter(u);

    return MapIter{rmiter};
}

Unit *
Map::removeUnitAt(Vec2 at)
{
    RectMapIter rmiter = _rm.iterAt(at);
    Cell &cell = rmiter.cell();
    Unit *u = dynamic_cast<Unit *>(cell.unit());

    if (u) {
        --_units_count;
        cell.landscape()->onLeave(u);
        if (auto *n = dynamic_cast<NeutralObject *>(cell.object())) {
            n->onLeave(u);
        }

        cell.setUnit(nullptr);
        u->unsetPosition();
    }

    return u;
}

MapIter
Map::addPlaceable(Placeable *p, Vec2 pt)
{
    RectMapIter rmiter = _rm.iterAt(pt);
    Cell &cell = rmiter.cell();

    if (cell.object()) {
        return MapIter::makeNull();
    }

    cell.setObject(p);

    return MapIter{rmiter};
}

MapIter
Map::addBase(Base *b, Vec2 pt)
{
    return addPlaceable(b, pt);
}

MapIter
Map::addNeutralObject(NeutralObject *n, Vec2 pt)
{
    return addPlaceable(n, pt);
}

void
Map::setLandscape(Landscape *l, Vec2 pt)
{
    RectMapIter rmiter = _rm.iterAt(pt);
    Cell &cell = rmiter.cell();
    cell.setLandscape(l);
}

Unit *
MapIter::unit() const
{
    return _it.cell().unit();
}

bool
MapIter::moveUnitTo(MapIter to) const
{
    auto &sc = _it.cell();
    auto &dc = to._it.cell();

    if (!sc.unit()
        || dc.unit()) {
        return false;
    }

    Unit *u = sc.unit();
    
    dc.setUnit(u);
    u->setPosition(to.point());
    sc.setUnit(nullptr);

    return true;
}

Base *
MapIter::base() const
{
    return dynamic_cast<Base *>(_it.cell().object());
}

NeutralObject *
MapIter::neutralObject() const
{
    return dynamic_cast<NeutralObject *>(_it.cell().object());
}

Landscape *
MapIter::landscape() const
{
    return _it.cell().landscape();
}
