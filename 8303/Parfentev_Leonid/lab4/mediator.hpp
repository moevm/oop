#ifndef _H_MEDIATOR_HPP
#define _H_MEDIATOR_HPP

#include "point.hpp"
#include "map.hpp"
#include "unit.hpp"


class Mediator {
    Map *_map;

public:
    Mediator(Map *map)
        :_map{map} {}

    MapInfo infoAt(Vec2 pt);

    Vec2 mapSize();

    bool moveUnitTo(Unit *u, Vec2 to);

    bool attackTo(Unit *u, Vec2 to);

    bool useObject(Unit *u);

    bool spawnUnit(Unit *u, Vec2 at);
    bool teleportUnit(Unit *u, Vec2 to);
};


#endif
