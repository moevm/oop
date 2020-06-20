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

#include "base.hpp"
#include "landscape.hpp"
#include "landscape_types.hpp"
#include "neutral_object.hpp"
#include "neutral_object_types.hpp"
#include "unit_factory.hpp"


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
            os << class_chars.at(std::type_index{typeid(*u)});
        } else {
            auto *l = iter.landscape();
            os << class_chars.at(std::type_index{typeid(*l)});
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
              << " with " << u->health() << " HP at "
              << u->position();
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

class EventPrinter: public EventListener {
    std::ostream *_os;
    std::string _prefix;

public:
    EventPrinter(std::ostream &os, const std::string &prefix)
        :_os{&os}, _prefix{prefix} {}

    virtual void
    handle(Event *e) override
    {
        if (dynamic_cast<UnitLiveDeletedEvent *>(e))
            return;

        (*_os) << _prefix << ": ";

        if (auto *ee = dynamic_cast<UnitAddedEvent *>(e)) {
            (*_os) << "Unit added: " << ee->unit() << "\n";

        } else if (auto *ee = dynamic_cast<UnitDeathEvent *>(e)) {
            (*_os) << "Unit died: " << ee->unit() << "\n";

        } else if (auto *ee = dynamic_cast<UnitTakesDamageEvent *>(e)) {
            (*_os) << "Unit " << ee->unit() << " takes "
                   << ee->damage() << " health points of damage\n";

        } else if (auto *ee = dynamic_cast<UnitGetsHealedEvent *>(e)) {
            (*_os) << "Unit " << ee->unit() << " gets healed by "
                   << ee->health() << " health points\n";

        } else if (auto *ee = dynamic_cast<UnitAttackedEvent *>(e)) {
            (*_os) << "Unit " << ee->attacker()
                   << " attacked another unit " << ee->target() << "\n";

        } else if (auto *ee = dynamic_cast<UnitWasAttackedEvent *>(e)) {
            (*_os) << "Unit " << ee->target()
                   << " was attacked by another unit "
                   << ee->attacker() << "\n";

        } else {
            (*_os) << "Unknown event\n";
        }
    }
};

MapIter
doAttack(Unit *u, MapIter to)
{
    if (!u->canAttackTo(to)) {
        return MapIter::makeNull();

    } else {
        auto pos = u->actualPosition(to);

        if (Unit *targ = pos.unit()) {
            auto dam = u->baseAttack(to);
            targ->takeDamage(
                targ->actualDamage(
                    dam.first, dam.second).evaluate());
            return pos;
        }

        return MapIter::makeNull();
    }
}

class FactoryTable: public UnitCreationStrategy {
    std::map<std::string, UnitFactory *> _tab {};

    void
    registerFactory(const std::string &key, UnitFactory *f)
    {
        _tab[key] = f;
    }

public:
    FactoryTable()
    {
#define REG(k, T)                                   \
        registerFactory(                            \
            k, new SimpleUnitFactory<units::T> {})
        REG("swordsman", Swordsman);
        REG("spearsman", Spearsman);
        REG("cavalry", Cavalry);
        REG("archer", Archer);
        REG("slinger", Slinger);
        REG("onager", Onager);
        REG("boltthrower", BoltThrower);
#undef REG
    }

    virtual bool
    canCreate(const std::string &key) const override
    {
        return _tab.find(key) != _tab.end();
    }

    virtual std::vector<std::string>
    keys() const override
    {
        std::vector<std::string> keys {};
        for (auto p: _tab) {
            keys.push_back(p.first);
        }
        return keys;
    }

    virtual Unit *
    create(const std::string &key) override
    {
        auto iter = _tab.find(key);
        if (iter == _tab.end()) {
            return nullptr;
        }

        return iter->second->create();
    }

    virtual ~FactoryTable() override
    {
        for (auto p: _tab) {
            delete p.second;
        }
    }
};

struct SimpleGame {
    Map *map;
    Base *b1, *b2;
    EventPrinter *pr1, *pr2;

    explicit SimpleGame(int w=10, int h=10,
                        int x1=1, int y1=1,
                        int x2=9, int y2=9)
    {
        map = new Map {w, h};
        b1 = new Base {new FactoryTable {}};
        pr1 = new EventPrinter {std::cout, "Base 1"};

        map->addBase(b1, {x1, y1});
        b1->subscribe(pr1);

        b2 = new Base {new FactoryTable {}};
        pr2 = new EventPrinter {std::cout, "Base 2"};

        map->addBase(b2, {x2, y2});
        b2->subscribe(pr2);
    }

    ~SimpleGame()
    {
        delete map;
        delete pr1;
        delete pr2;
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
setupUnit(Base *base, const std::string &k, Map *map, Vec2 pt)
{
    Unit *u = base->createUnit(k);

    if (map->addUnit(u, pt).null()) {
        base->removeUnit(u);
        delete u;
        return nullptr;
    }

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

    auto u1 = setupUnit(g.b1, "swordsman", g.map, {2, 2});
    auto u2 = setupUnit(g.b2, "swordsman", g.map, {3, 2});

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

    auto u3 = setupUnit(g.b1, "spearsman", g.map, {3, 8});
    auto u4 = setupUnit(g.b1, "spearsman", g.map, {7, 8});
    auto u5 = setupUnit(g.b2, "onager", g.map, {5, 5});

    while (u3->alive())
        doAttack(u5, g.map->iterAt(u3->position()));

    while (u4->alive())
        doAttack(u5, g.map->iterAt(u4->position()));
}

bool
doUseObject(MapIter u_iter)
{
    auto *u = u_iter.unit();
    auto *n = u_iter.neutralObject();

    if (!n->canUse(u, u_iter)) {
        return false;
    }

    n->onUse(u, u_iter);
    return true;
}

void
demo6()
{
    SimpleGame g {};

    auto *u1 = setupUnit(g.b1, "slinger", g.map, {1, 5});
    auto *u2 = setupUnit(g.b2, "swordsman", g.map, {6, 5});

    auto u1_iter = g.map->iterAt(u1->position());
    auto u2_iter = g.map->iterAt(u2->position());

    g.map->addNeutralObject(new objects::Tower {}, {1, 5});
    g.map->addNeutralObject(new objects::HealingWell {}, {6, 5});

    if (doAttack(u1, u2_iter).null()) {
        std::cout << u1 << " can't reach " << u2 << "\n";
    } else {
        std::cout << u1 << " somehow reached " << u2 << "\n";
    }

    if (doUseObject(u1_iter)) {
        std::cout << u1 << " used the tower\n";
    } else {
        std::cout << u1 << " can't use the tower\n";
    }

    if (doAttack(u1, u2_iter).null()) {
        std::cout << u1 << " still can't reach " << u2 << "\n";
    }

    std::cout << "u1: " << u1 << "\n";
    std::cout << "u2: " << u2 << "\n";

    if (doUseObject(u2_iter)) {
        std::cout << u2 << " used the healing well\n";
    }

    std::cout << "u1: " << u1 << "\n";
    std::cout << "u2: " << u2 << "\n";
}
