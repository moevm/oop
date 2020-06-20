#include <iostream>
#include <string>

#include "base.hpp"
#include "game.hpp"
#include "event.hpp"
#include "event_types.hpp"
#include "storable.hpp"
#include "common_storables.hpp"


Game::Game(Map *map)
    :_map{map},
     _med{new Mediator {map}}
{
    this->subscribe(_log_sink);
}

int
Game::addBase(Base *base)
{
    base->subscribe(_coll);
    base->subscribe(this);

    _recs.push_back(BaseRecord{base, nullptr});

    return (int)(_recs.size() - 1);
}

void
Game::setPlayer(int base_idx, Player *p)
{
    Player *&p_place = _recs[base_idx].player;
    if (p_place) {
        p_place->unsubscribe(_log_sink);
        delete p_place;
        --_players;
    }
    p_place = p;
    if (p) {
        p->subscribe(_log_sink);
        ++_players;
    }
}

int
Game::basesCount() const
{
    return _recs.size();
}

int
Game::playersCount() const
{
    return _players;
}

Base *
Game::baseByIdx(int idx) const
{
    return _recs[idx].base;
}

void
Game::spin()
{
    auto &rec = _recs[_next];
    Player *p = rec.player;
    Base *b = rec.base;

    if (p) {
        emit(new events::TurnStarted {p});

        bool res = p->takeTurn(this, _med, b);

        _coll->collect(_map);

        emit(new events::TurnOver {p});

        if (!res) {
            setPlayer(_next, nullptr);
        }
    }

    if (++_next == (int)_recs.size()) {
        _next = 0;
    }
}

void
Game::store(std::ostream &os) const
{
    os << "game\n";
    _map->store(os);

    os << _next << "\n";

    for (int i = 0; i < basesCount(); ++i) {
        auto *b = baseByIdx(i);

        StorableWithCoords::storeWithCoords(b->position(), b, os);

        for (auto iter = b->unitsBegin();
             iter != b->unitsEnd();
             ++iter) {
            auto *u = iter.unit();
            auto *sc = new StorableWithCoords {u->position(), u};
            StorableWithIndex::storeWithIndex(i, sc, os);
        }
    }

    for (int i = 0; i < basesCount(); ++i) {
        auto *p = _recs[i].player;
        if (p) {
            StorableWithIndex::storeWithIndex(i, p, os);
        }
    }

    os << "end\n";
}

bool
Game::restore(std::istream &is,
              RestorerTable *tab)
{
    is >> _next;

    for (;;) {
        Storable *s = tab->restore(is);
        if (auto *sc =
            dynamic_cast<StorableWithCoords *>(s)) {
            if (auto *b
                = dynamic_cast<Base *>(sc->child())) {
                _map->addBase(b, sc->coords());
                addBase(b);
            } else {
                delete sc->child();
                delete sc;
                return false;
            }
            delete sc;
        } else if (auto *si =
                   dynamic_cast<StorableWithIndex *>(s)) {
            if (auto *p
                = dynamic_cast<Player *>(si->child())) {
                if (si->index() < 0
                    || si->index() >= basesCount()) {
                    delete p;
                    delete si;
                    return false;
                }
                setPlayer(si->index(), p);
            } else if (auto *sc =
                       dynamic_cast<StorableWithCoords *>(
                           si->child())) {
                if (auto *u
                    = dynamic_cast<Unit *>(sc->child())) {
                    _map->addUnit(u, sc->coords());
                    baseByIdx(si->index())->addUnit(u);
                    delete sc;
                } else {
                    delete si;
                    delete sc;
                    delete sc->child();
                    return false;
                }
            } else {
                delete si->child();
                delete si;
                return false;
            }
            delete si;
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

Game::~Game()
{
    for (int i = 0; i < (int)_recs.size(); ++i) {
        setPlayer(i, nullptr);
        auto &rec = _recs[i];
        rec.base->unsubscribe(this);
        rec.base->unsubscribe(_coll);
    }

    delete _coll;
    delete _map;

    delete _log_sink;
}
