#include <iostream>
#include <map>
#include <typeinfo>
#include <typeindex>
#include <string>

#include "point.hpp"
#include "map.hpp"
#include "unit.hpp"
#include "melee_units.hpp"
#include "ranged_units.hpp"
#include "catapult_units.hpp"


#define UNIT_ENTRY(T, x) {std::type_index{typeid(units::T)}, x}
static const std::map<std::type_index, char> unit_chars {
    UNIT_ENTRY(Swordsman,   'S'),
    UNIT_ENTRY(Spearsman,   'P'),
    UNIT_ENTRY(Cavalry,     'C'),
    UNIT_ENTRY(Archer,      'A'),
    UNIT_ENTRY(Slinger,     's'),
    UNIT_ENTRY(Onager,      'O'),
    UNIT_ENTRY(BoltThrower, 'B'),
};
#undef UNIT_ENTRY

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

std::ostream &
operator<<(std::ostream &os, Map *map)
{
    for (MapIter iter = map->begin();
         iter != map->end();
         iter.advance(1)) {

        if (Unit *u = iter.unit()) {
            os << unit_chars.at(std::type_index{typeid(*u)});
        } else {
            os << ".";
        }

        os << ((iter.x() == map->width() - 1) ? "\n" : " ");
    }
    return os;
}

std::ostream &
operator<<(std::ostream &os, Vec2 pt)
{
    return os << "{" << pt.x() << "," << pt.y() << "}";
}

std::ostream &
operator<<(std::ostream &os, Unit *u)
{
    return os << "a "
              << unit_names.at(std::type_index{typeid(*u)})
              << " with " << u->health() << " HP";
}

void
demo1()
{
    // create a map
    auto *map = new Map {10, 10};

    // create a few units
    auto sw1_iter = map->addUnit(new units::Swordsman {}, {3, 3});
    map->addUnit(new units::Swordsman {}, {4, 4});

    // write the map
    std::cout << map << "\n";

    // test the pathfinder
    static const std::vector<Vec2> pts {
        {3, 4},
        {3, 3},
        {5, 5},
        {5, 4},
        {5, 3},
    };
    for (auto pt: pts) {
        std::cout << sw1_iter.unit() << " at " << sw1_iter.point() << " "
                  << ((sw1_iter.unit()->canMove(map->iterAt(pt)))
                      ? "can" : "can't")
                  << " move to " << pt << "\n";
    }

    // clean up
    delete map;
}

void
demo2()
{
    auto *map = new Map {10, 10};

    auto c_iter = map->addUnit(new units::Cavalry {}, {3, 3});
    auto *u = c_iter.unit();

    std::cout << map << "\n";

    static const std::vector<Vec2> path {
        {4, 5}, {6, 5}, {9, 5}, {8, 7}, {7, 9},
    };
    for (auto pt: path) {
        auto to = map->iterAt(pt);

        if (!u->canMove(to)) {
            std::cout << u << " at " << u->position()
                      << " can't move to " << pt << "!\n";
            break;
        }

        std::cout << "moving " << u << " at " << u->position()
                  << " to " << pt << "...\n";

        c_iter = map->addUnit(map->removeUnitAt(c_iter), pt);
        if (c_iter.null()) {
            std::cout << "failed!\n";
        }
    }

    std::cout << "\n" << map;

    delete map;
}

void
demo3()
{
    auto *map = new Map {10, 10};
    map->setMaxUnitsCount(2);

    Unit *sw = new units::Swordsman {};
    Unit *ar = new units::Archer {};

    map->addUnit(sw, {5, 0});
    map->addUnit(ar, {5, 9});

    Unit *x = new units::Swordsman {};
    if (!map->addUnit(x, {1, 1}).null()) {
        std::cout << "Added one more unit!\n";
        delete map->removeUnitAt({1, 1});
    } else {
        std::cout << "Max units: " << map->maxUnitsCount()
                  << ", current units: " << map->unitsCount()
                  << "\n";
        delete x;
    }

    std::cout << map;

    while (sw->alive() && ar->alive()) {
        Vec2 from = sw->position();
        Vec2 to = from.shifted({0, 1});

        std::cout << "\nmoving " << sw << " from " << from
                  << " to " << to << "...\n";

        if (!sw->canMove(map->iterAt(to))) {
            std::cout << "can't move\n";
            break;
        }

        if (map->addUnit(map->removeUnitAt(from), to).null()) {
            std::cout << "failed\n";
            break;
        }

        std::cout << ar << " shoots at " << sw->position() << "...\n";

        auto toi = map->iterAt(sw->position());
        if (!ar->canAttackTo(toi)) {
            std::cout << "can't shoot\n";
            // it’s ok
        } else {
            auto pos = ar->actualPosition(toi);
            if (Unit *targ = pos.unit()) {
                auto dam = ar->baseAttack(toi);

                std::cout << "hits " << targ << "\n";

                targ->takeDamage(
                    targ->actualDamage(
                        dam.first, dam.second).evaluate());

                std::cout << "now: " << targ << "\n";
            }
        }
    }
}
