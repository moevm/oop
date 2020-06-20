#include <iostream>

#include "point.hpp"
#include "unit.hpp"
#include "placeable.hpp"
#include "base.hpp"
#include "neutral_object.hpp"
#include "landscape.hpp"
#include "map.hpp"
#include "storable.hpp"
#include "common_storables.hpp"


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
    p->setPosition(pt);

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

void
Map::store(std::ostream &os) const
{
    os << "map " << width() << " " << height() << "\n";
    os << _units_max << "\n";

    for (int y = 0; y < height(); ++y) {
        for (int x = 0; x < width(); ++x) {
            auto info = infoAt({x, y});

            const auto *l = info.landscape();
            if (!dynamic_cast<const landscapes::Normal *>(l)) {
                StorableWithCoords::storeWithCoords({x, y}, l, os);
            } else if (const auto *n = info.neutralObject()) {
                StorableWithCoords::storeWithCoords({x, y}, n, os);
            }

            // bases and units are restored in Game::restore
        }
    }

    os << "end\n";
}

bool
Map::restore(std::istream &is,
             RestorerTable *tab)
{
    is >> _units_max;
    if (is.fail()) {
        return false;
    }

    for (;;) {
        Storable *s = tab->restore(is);

        if (auto *sc =
            dynamic_cast<StorableWithCoords *>(s)) {
            if (auto *l =
                dynamic_cast<Landscape *>(sc->child())) {
                setLandscape(l, sc->coords());
                delete sc;
            } else if (auto *n =
                       dynamic_cast<NeutralObject *>(sc->child())) {
                addNeutralObject(n, sc->coords());
                delete sc;
            } else {
                delete sc->child();
                delete sc;
                return false;
            }
        } else if (dynamic_cast<StorableEnd *>(s)) {
            delete s;
            break;
        } else {
            delete s;
            return false;
        }
    }

    return true;
}

MapInfo
Map::infoAt(Vec2 pt) const
{
    return MapInfo{&_rm.at(pt)};
}

Unit *
MapIter::unit() const
{
    return _it.cell().unit();
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

const Landscape *
MapInfo::landscape() const
{
    return _cell->landscape();
}

const Unit *
MapInfo::unit() const
{
    return _cell->unit();
}

const Base *
MapInfo::base() const
{
    return dynamic_cast<Base *>(_cell->object());
}

const NeutralObject *
MapInfo::neutralObject() const
{
    return dynamic_cast<NeutralObject *>(_cell->object());
}
