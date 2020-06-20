#ifndef _H_GAME_RULES_HPP
#define _H_GAME_RULES_HPP

#include <iostream>
#include <utility>

#include "map.hpp"
#include "game.hpp"
#include "iostream_player.hpp"
#include "game_driver.hpp"
#include "landscape_types.hpp"


class BaseWithSpawnCountdown: public Base {
    int _cd_max;
    int _cd = 0;

public:
    BaseWithSpawnCountdown(int cd_max=0)
        :_cd_max{cd_max} {}

    virtual bool
    canCreateUnit(const std::string &key) const override
    {
        return _cd == 0
            && Base::canCreateUnit(key);
    }

    virtual int
    createUnit(const std::string &key, Mediator *m) override
    {
        int id = Base::createUnit(key, m);
        if (id < 0) {
            return id;
        }

        _cd = _cd_max;
        return id;
    }

    virtual void
    store(std::ostream &os) const override
    {
        os << "base_w_countdown " << maxUnitsCount()
           << " " << destroyed() << " " << _cd_max << " "
           << _cd << "\n";
    }

    virtual bool
    restore(std::istream &is, RestorerTable *tab) override
    {
        if (!Base::restore(is, tab)) {
            return false;
        }

        is >> _cd_max >> _cd;
        return !is.fail();
    }

    virtual void
    spin() override
    {
        if (_cd > 0) {
            --_cd;
        }
    }
};

class DefaultRules: public GameRules {
protected:
    static void
    addBaseAndPlayer(Game *g, Map *m,
                     std::string name, int x, int y)
    {
        Base *b = new BaseWithSpawnCountdown {5};
        m->addBase(b, {x, y});
        int id = g->addBase(b);

        auto *p = new IostreamPlayer {std::move(name)};
        p->setOstream(std::cout);
        p->setIstream(std::cin);
        g->setPlayer(id, p);
    }

public:
    virtual Map *makeMap() override
    {
        return new Map {10, 10};
    }

    virtual void setup(Game *g, Map *m) override
    {
        addBaseAndPlayer(g, m, "Player 1", 1, 1);
        addBaseAndPlayer(g, m, "Player 2", 8, 8);
    }

    virtual bool gameEnded(Game *g) override
    {
        return g->playersCount() < 2;
    }

    virtual int winner(Game *g) override
    {
        int n = g->basesCount();
        int only = -1;

        for (int i = 0; i < n; ++i) {
            if (!g->baseByIdx(i)->destroyed()) {
                if (only < 0) {
                    only = i;
                } else {
                    return -1;
                }
            }
        }

        return only;
    }
};

class FancyRules: public DefaultRules {
    virtual Map *makeMap() override
    {
        Map *m = new Map {15, 15};

        for (int y = 0; y < 5; ++y) {
            for (int x = 0; x < 5; ++x) {
                m->setLandscape(new landscapes::Forest {},
                                {5+x, 5+y});
            }
        }

        return m;
    }

    virtual void setup(Game *g, Map *m) override
    {
        addBaseAndPlayer(g, m, "Player 1", 3, 3);
        addBaseAndPlayer(g, m, "Player 2", 3, 11);
        addBaseAndPlayer(g, m, "Player 3", 11, 11);
        addBaseAndPlayer(g, m, "Player 4", 11, 3);
    }
};

#endif
