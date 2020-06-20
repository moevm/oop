#include "base.hpp"
#include "game.hpp"
#include "event.hpp"
#include "event_types.hpp"


int
Game::addBase(Base *base)
{
    base->subscribe(_coll);
    base->subscribe(this);

    _recs.push_back(BaseRecord{base, nullptr});

    emit(new events::BaseAdded {base});

    return (int)(_recs.size() - 1);
}

void
Game::setPlayer(int base_idx, Player *p)
{
    Player *&p_place = _recs[base_idx].player;
    if (p_place) {
        delete p_place;
        --_players;
    }
    p_place = p;
    if (p) {
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

        bool res = p->takeTurn(_med, b);

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
}
