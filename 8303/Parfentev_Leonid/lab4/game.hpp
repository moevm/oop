#ifndef _H_GAME_HPP
#define _H_GAME_HPP

#include <vector>

#include "event.hpp"
#include "map.hpp"
#include "base.hpp"
#include "player.hpp"
#include "zombie_collector.hpp"
#include "mediator.hpp"


class Game: public EventForwarder {
    Map *_map;
    Mediator *_med;

    struct BaseRecord {
        Base *base;
        Player *player;
    };

    std::vector<BaseRecord> _recs {};
    int _next = 0;
    int _players = 0;

    ZombieCollector *_coll {new ZombieCollector {}};

    EventForwarder *_log_sink {new EventForwarder {}};

public:
    Game(Map *map);

    int addBase(Base *b);
    void setPlayer(int base_idx, Player *p);

    int basesCount() const;
    int playersCount() const;

    Base *baseByIdx(int idx) const;

    EventForwarder *logSink() const { return _log_sink; }

    void spin();

    ~Game();
};


#endif
