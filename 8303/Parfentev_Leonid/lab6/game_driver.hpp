#ifndef _H_GAME_DRIVER_HPP
#define _H_GAME_DRIVER_HPP

#include "map.hpp"
#include "game.hpp"


class GameRules {
public:
    virtual Map *makeMap() =0;
    virtual void setup(Game *g, Map *m) =0;
    virtual bool gameEnded(Game *g) =0;
    virtual int winner(Game *g) =0;
};

template<typename Rules>
class GameDriver: public ResetHandler {

    Game *_g = nullptr;
    Game *_g_reset = nullptr;   // required to reset game while running
    Rules *_r {new Rules {}};

    std::vector<EventPrinter *> _loggers {};
    EventPrinter *_printer = nullptr;

    Game *init()
    {
        Map *m = _r->makeMap();
        Game *g = new Game {m};
        _r->setup(g, m);
        return g;
    }

    void setBasePrefixes(EventPrinter *p)
    {
        int n = _g->basesCount();
        for (int i = 0; i < n; ++i) {
            std::ostringstream oss {};
            oss << "Base " << (i+1);
            p->setPrefix(_g->baseByIdx(i), oss.str());
        }
    }

public:
    void
    addLogger(EventPrinter *l)
    {
        _loggers.push_back(l);
        if (_g) {
            _g->logSink()->subscribe(l);
            setBasePrefixes(l);
        }
    }

    void
    setPrinter(EventPrinter *pr)
    {
        if (_printer) {
            if (_g) {
                _g->unsubscribe(_printer);
            }
            delete _printer;
        }

        _printer = pr;
        if (_g && _printer) {
            _g->subscribe(_printer);
            setBasePrefixes(_printer);
        }
    }

    virtual void reset() override
    {
        resetFrom(init());
    }

    void resetFrom(Game *g)
    {
        _g_reset = g;
    }

    void run()
    {
        for (;;) {
            if (_g_reset) {
                delete _g;
                _g = _g_reset;
                _g_reset = nullptr;
                _g->setResetHandler(this);

                if (_printer) {
                    _g->subscribe(_printer);
                    setBasePrefixes(_printer);
                }
                for (auto *l: _loggers) {
                    _g->logSink()->subscribe(l);
                    setBasePrefixes(l);
                }
            }
            if (_r->gameEnded(_g)) {
                break;
            }
            _g->spin();
        }
    }

    int winner()
    {
        return _r->winner(_g);
    }

    virtual ~GameDriver() override
    {
        delete _g;
        delete _g_reset;
        delete _printer;
        for (auto *l: _loggers) {
            delete l;
        }
    }
};

#endif
