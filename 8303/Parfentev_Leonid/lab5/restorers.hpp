#ifndef _H_RESTORERS_HPP
#define _H_RESTORERS_HPP

#include "storable.hpp"

#include "point.hpp"
#include "map.hpp"
#include "unit.hpp"

#include "base.hpp"
#include "game.hpp"
#include "player.hpp"


template<typename T>
class SimpleRestorer: public Restorer {
public:
    virtual Storable *
    restore(std::istream &,
            RestorerTable *) const override
    {
        return new T {};
    }
};


namespace restorers {

    class GameRestorer: public Restorer {
    public:
        virtual Storable *
        restore(std::istream &is,
                RestorerTable *tab) const override
        {
            Storable *s = tab->restore(is);
            Map *map = dynamic_cast<Map *>(s);
            if (!map) {
                delete s;
                return nullptr;
            }

            return new Game {map};
        }
    };

    class MapRestorer: public Restorer {
    public:
        virtual Storable *
        restore(std::istream &is,
                RestorerTable *) const override
        {
            int w, h;
            is >> w >> h;

            return new Map {w, h};
        }
    };

}

#endif
