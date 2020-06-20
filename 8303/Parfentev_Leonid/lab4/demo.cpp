#include <iostream>
#include <map>
#include <typeinfo>
#include <typeindex>
#include <string>
#include <utility>
#include <sstream>

#include "point.hpp"
#include "map.hpp"
#include "unit.hpp"
#include "melee_units.hpp"
#include "ranged_units.hpp"
#include "catapult_units.hpp"

#include "event.hpp"
#include "event_types.hpp"
#include "base.hpp"
#include "landscape.hpp"
#include "landscape_types.hpp"
#include "neutral_object.hpp"
#include "neutral_object_types.hpp"
#include "unit_factory.hpp"

#include "game.hpp"
#include "event_printer.hpp"
#include "iostream_player.hpp"

#include "factory_table.hpp"


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
        std::cout << sw1_iter.unit() << " "
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
            std::cout << u << " can't move to " << pt << "!\n";
            break;
        }

        std::cout << "moving " << u
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

MapIter
doAttack(Unit *u, MapIter to)
{
    if (!u->canAttackTo(to)) {
        return MapIter::makeNull();

    } else {
        auto pos = u->actualPosition(to);

        if (Unit *targ = pos.unit()) {
            auto dam = u->baseAttack(pos);
            targ->takeDamage(
                targ->actualDamage(
                    dam.first, dam.second).evaluate());
            return pos;
        }

        return MapIter::makeNull();
    }
}

struct SimpleGame {
    Map *map;
    Base *b1, *b2;
    EventPrinter *pr;

    explicit SimpleGame(int w=10, int h=10,
                        int x1=1, int y1=1,
                        int x2=9, int y2=9)
    {
        pr = new EventPrinter {std::cout};

        map = new Map {w, h};

        b1 = new Base {};
        pr->setPrefix(b1, "Base 1");

        map->addBase(b1, {x1, y1});
        b1->subscribe(pr);

        b2 = new Base {};
        pr->setPrefix(b2, "Base 2");

        map->addBase(b2, {x2, y2});
        b2->subscribe(pr);
    }

    ~SimpleGame()
    {
        delete map;
        delete pr;
    }
};

void
demo4()
{
    SimpleGame g {};

    Unit *u1 = new units::Swordsman {};
    Unit *u2 = new units::Swordsman {};

    g.b1->addUnit(u1);
    g.b2->addUnit(u2);

    g.map->addUnit(u1, {3, 3});
    g.map->addUnit(u2, {4, 3});

    while (u1->alive()
           && u2->alive()) {
        doAttack(u1, g.map->iterAt(u2->position()));
        if (u2->alive()) {
            doAttack(u2, g.map->iterAt(u1->position()));
        }
    }
}

MapIter
doMove(Map *map, const Unit *u, Vec2 pt)
{
    auto from = map->iterAt(u->position());
    auto to = map->iterAt(pt);

    if (!u->canMove(to)) {
        return MapIter::makeNull();
    }

    return map->addUnit(map->removeUnitAt(from), pt);
}

Unit *
setupUnit(Base *base, const std::string &k, Mediator *m, Vec2 pt)
{
    Unit *u = base->getUnitById(base->createUnit(k, m));
    m->teleportUnit(u, pt);
    return u;
}

void
demo5()
{
    SimpleGame g {};

    // 2,2 .. 5,5: swamp
    for (int j = 0; j < 3; ++j) {
        for (int i = 0; i < 3; ++i) {
            g.map->setLandscape(new landscapes::Swamp {},
                                {2+i, 2+j});
        }
    }

    // 1,7 .. 6,9: forest
    for (int j = 0; j < 2; ++j) {
        for (int i = 0; i < 5; ++i) {
            g.map->setLandscape(new landscapes::Forest {},
                                {1+i, 7+j});
        }
    }

    auto *m = new Mediator {g.map};
    auto u1 = setupUnit(g.b1, "swordsman", m, {2, 2});
    auto u2 = setupUnit(g.b2, "swordsman", m, {3, 2});

    if (doMove(g.map, u1, {0, 2}).null()) {
        std::cout << "Can't move " << u1 << " across 2 cells\n";
    } else {
        std::cout << "Moved " << u1 << " across 2 cells \n";
    }

    std::cout << "u1: " << u1 << "\n";

    if (doAttack(u1, g.map->iterAt(u2->position())).null()) {
        std::cout << "Can't attack in swamp\n";
    } else {
        std::cout << "Attacked in a swamp\n";
    }

    std::cout << "u2: " << u2 << "\n";

    doMove(g.map, u1, {1, 2});
    doMove(g.map, u2, {2, 3});

    std::cout << "u1: " << u1 << "\n";
    std::cout << "u2: " << u2 << "\n";

    doAttack(u1, g.map->iterAt(u2->position()));

    auto u3 = setupUnit(g.b1, "spearsman", m, {3, 8});
    auto u4 = setupUnit(g.b1, "spearsman", m, {7, 8});
    auto u5 = setupUnit(g.b2, "onager", m, {5, 5});

    while (u3->alive())
        doAttack(u5, g.map->iterAt(u3->position()));

    while (u4->alive())
        doAttack(u5, g.map->iterAt(u4->position()));

    std::cout << g.map;

    delete m;
}

void
demo6()
{
    SimpleGame g {};

    auto *m = new Mediator {g.map};
    auto *u1 = setupUnit(g.b1, "slinger", m, {1, 5});
    auto *u2 = setupUnit(g.b2, "swordsman", m, {6, 5});

    g.map->addNeutralObject(new objects::Tower {}, {1, 5});
    g.map->addNeutralObject(new objects::HealingWell {}, {6, 5});

    if (m->attackTo(u1, u2->position())) {
        std::cout << u1 << " can't reach " << u2 << "\n";
    } else {
        std::cout << u1 << " somehow reached " << u2 << "\n";
    }

    if (m->useObject(u1)) {
        std::cout << u1 << " used the tower\n";
    } else {
        std::cout << u1 << " can't use the tower\n";
    }

    if (m->attackTo(u1, u2->position())) {
        std::cout << u1 << " still can't reach " << u2 << "\n";
    }

    std::cout << "u1: " << u1 << "\n";
    std::cout << "u2: " << u2 << "\n";

    if (m->useObject(u2)) {
        std::cout << u2 << " used the healing well\n";
    }

    std::cout << "u1: " << u1 << "\n";
    std::cout << "u2: " << u2 << "\n";
}

void
demo7()
{
    class MoverPlayer: public Player {
        std::string _unit_type;
        int _id = -1;

    public:
        using Player::Player;

        MoverPlayer(std::string name,
                    std::string type)
            :Player{name}, _unit_type{std::move(type)} {}

        virtual bool
        takeTurn(Mediator *m, Base *b) override
        {
            if (_id >= 0) {
                Unit *u = b->getUnitById(_id);
                m->moveUnitTo(u, u->position().shifted({1, 0}));
            } else {
                _id = b->createUnit(_unit_type, m);
            }
            return true;
        }
    };

    auto *map = new Map {10, 10};

    Game g {map};

    auto *pr = new EventPrinter {std::cout};
    g.subscribe(pr);

    auto *b = new Base {};
    map->addBase(b, {3, 3});
    int b_id = g.addBase(b);

    auto *p = new MoverPlayer {"Player 1", "swordsman"};
    g.setPlayer(b_id, p);

    for (int i = 0; i < 5; ++i)
        g.spin();

    g.unsubscribe(pr);
    delete pr;
}

void
demo8()
{
    auto *map = new Map {10, 10};

    Game g {map};

    auto *pr = new EventPrinter {std::cout};
    g.subscribe(pr);

    std::stringstream s1 {};
    s1 << "base\n"
       << "create spearsman\n"
       << "map 0 0 9 9\n"
       << "move 0  3 5\n"
       << "map 0 0 9 9\n"
       << "describe 3 5\n";

    auto *b1 = new Base {};
    map->addBase(b1, {3, 3});
    int b1_id = g.addBase(b1);

    auto *p1 = new IostreamPlayer {"Player 1"};
    p1->setOstream(std::cout);
    p1->setIstream(s1);
    g.setPlayer(b1_id, p1);

    std::stringstream s2 {};
    s2 << "create archer\n"
       << "attack 0  3 5\n";

    auto *b2 = new Base {};
    map->addBase(b2, {7, 3});
    int b2_id = g.addBase(b2);

    auto *p2 = new IostreamPlayer {"Player 2"};
    p2->setOstream(std::cout);
    p2->setIstream(s2);
    g.setPlayer(b2_id, p2);

    while (g.playersCount())
        g.spin();

    g.unsubscribe(pr);
    delete pr;
}

void
demo9()
{
    Map *map = new Map {10, 10};

    auto *uf = (new objects
                ::WeaponSmiths
                ::SimpleUnitFilter<BasicCatapultUnit> {});
    auto *ws = new objects::WeaponSmiths {2.0, uf};
    map->addNeutralObject(ws, {3, 4});

    Game g {map};

    auto *pr = new EventPrinter {std::cout};
    g.subscribe(pr);

    Base *b1 = new Base {};
    map->addBase(b1, {3, 3});
    int b1_id = g.addBase(b1);

    Base *b2 = new Base {};
    map->addBase(b2, {7, 3});
    int b2_id = g.addBase(b2);

    std::stringstream s1 {};
    std::stringstream s2 {};

    s1 << "create onager\n"
       << "move 0  3 4\n"
       << "use 0\n"
       << "create onager\n"
       << "move 1  3 2\n"
       << "attack 0  7 4\n"
       << "attack 1  7 2\n"
       << "create swordsman\n"
       << "move 0  3 5\n"
       << "move 2  3 4\n"
       << "use 2\n";

    s2 << "create swordsman\n"
       << "move 0  7 4\n"
       << "create swordsman\n"
       << "move 1  7 2\n"
       << "skip skip skip skip skip\n";

    auto *p1 = new IostreamPlayer {"Player 1"};
    p1->setOstream(std::cout);
    p1->setIstream(s1);
    g.setPlayer(b1_id, p1);

    auto *p2 = new IostreamPlayer {"Player 2"};
    p2->setOstream(std::cout);
    p2->setIstream(s2);
    g.setPlayer(b2_id, p2);

    while (g.playersCount())
        g.spin();

    g.unsubscribe(pr);
    delete pr;
}
