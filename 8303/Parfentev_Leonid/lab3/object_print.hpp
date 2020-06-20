#ifndef _H_OBJECT_PRINT_HPP
#define _H_OBJECT_PRINT_HPP

#include <iostream>
#include <map>
#include <string>

#include "point.hpp"
#include "map.hpp"
#include "unit.hpp"
#include "base.hpp"
#include "landscape.hpp"
#include "neutral_object.hpp"

std::ostream &
operator<<(std::ostream &os, Vec2 pt);

std::ostream &
operator<<(std::ostream &os, const Unit *u);

std::ostream &
operator<<(std::ostream &os, const Landscape *l);

std::ostream &
operator<<(std::ostream &os, const Base *b);

std::ostream &
operator<<(std::ostream &os, const NeutralObject *n);

std::ostream &
displayMapInfo(std::ostream &os, const MapInfo &info);

std::ostream &
displayMap(std::ostream &os, const Map *map,
         int x0, int y0, int x1, int y1);

std::ostream &
operator<<(std::ostream &os, const Map *map);

#endif
