#include <iostream>
#include <map>
#include <typeinfo>
#include <typeindex>
#include <string>

#include "point.hpp"
#include "unit.hpp"
#include "melee_units.hpp"
#include "ranged_units.hpp"
#include "catapult_units.hpp"
#include "base.hpp"
#include "neutral_object.hpp"
#include "neutral_object_types.hpp"
#include "landscape.hpp"
#include "landscape_types.hpp"
#include "object_print.hpp"


#define UNIT_ENTRY(T) {std::type_index{typeid(units::T)}, #T}
static const std::map<std::type_index, std::string> unit_names {
    UNIT_ENTRY(Swordsman),
    UNIT_ENTRY(Spearsman),
    UNIT_ENTRY(Cavalry),
    UNIT_ENTRY(Archer),
    UNIT_ENTRY(Slinger),
    UNIT_ENTRY(Onager),
    UNIT_ENTRY(BoltThrower),
};
#undef UNIT_ENTRY

#define LANDSCAPE_ENTRY(T) {std::type_index{typeid(landscapes::T)}, #T}
static const std::map<std::type_index, std::string> landscape_names {
    LANDSCAPE_ENTRY(Normal),
    LANDSCAPE_ENTRY(Swamp),
    LANDSCAPE_ENTRY(Forest),
};
#undef LANDSCAPE_ENTRY

#define N_OBJECT_ENTRY(T, n) {std::type_index{typeid(objects::T)}, n}
static const std::map<std::type_index, std::string> objects_names {
    N_OBJECT_ENTRY(HealingWell, "Healing Well"),
    N_OBJECT_ENTRY(Tower, "Tower"),
    N_OBJECT_ENTRY(TunnelsEntrance, "Tunnels Entrance"),
    N_OBJECT_ENTRY(WeaponSmiths, "Weapon Smiths"),
};
#undef N_OBJECT_ENTRY


std::ostream &
operator<<(std::ostream &os, Vec2 pt)
{
    return os << "{" << pt.x() << "," << pt.y() << "}";
}

std::ostream &
operator<<(std::ostream &os, const Unit *u)
{
    return os << "a "
              << unit_names.at(std::type_index{typeid(*u)})
              << " with " << u->health() << " HP at "
              << u->position();
}

std::ostream &
operator<<(std::ostream &os, const Landscape *l)
{
    return os << landscape_names.at(std::type_index{typeid(*l)});
}

std::ostream &
operator<<(std::ostream &os, const Base *b)
{
    os << "a Base with " << b->unitsCount();
    int m = b->maxUnitsCount();
    if (m >= 0) {
        os << "/" << m;
    }

    return os << " units at " << b->position();
}

std::ostream &
operator<<(std::ostream &os, const NeutralObject *n)
{
    return os << "a "
              << objects_names.at(std::type_index{typeid(*n)})
              << " at " << n->position();
}



static const std::map<std::type_index, char> class_chars {
#define UNIT_ENTRY(T, x) {std::type_index{typeid(units::T)}, x}
    UNIT_ENTRY(Swordsman,   'S'),
    UNIT_ENTRY(Spearsman,   'P'),
    UNIT_ENTRY(Cavalry,     'C'),
    UNIT_ENTRY(Archer,      'A'),
    UNIT_ENTRY(Slinger,     's'),
    UNIT_ENTRY(Onager,      'O'),
    UNIT_ENTRY(BoltThrower, 'B'),
#undef UNIT_ENTRY

#define LANDSCAPE_ENTRY(T, x)                   \
    {std::type_index{typeid(landscapes::T)}, x}
    LANDSCAPE_ENTRY(Normal, '.'),
    LANDSCAPE_ENTRY(Swamp,  '='),
    LANDSCAPE_ENTRY(Forest, '*'),
#undef LANDSCAPE_ENTRY
};

std::ostream &
displayMapInfo(std::ostream &os, const MapInfo &info)
{
    if (const Unit *u = info.unit()) {
        os << class_chars.at(std::type_index{typeid(*u)});
    } else if (info.base()) {
        os << "+";
    } else if (info.neutralObject()) {
        os << '#';
    } else {
        auto *l = info.landscape();
        os << class_chars.at(std::type_index{typeid(*l)});
    }

    return os;
}

std::ostream &
displayMap(std::ostream &os, const Map *map,
         int x0, int y0, int x1, int y1)
{
    for (int y = y0; y < y1; ++y) {
        for (int x = x0; x < x1; ++x) {
            displayMapInfo(os, map->infoAt({x, y}));
        }
        os << "\n";
    }
    return os;
}

std::ostream &
operator<<(std::ostream &os, const Map *map)
{
    return displayMap(os, map, 0, 0, map->width(), map->height());
}
