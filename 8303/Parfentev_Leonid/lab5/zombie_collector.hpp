#ifndef _H_ZOMBIE_COLLECTOR_HPP
#define _H_ZOMBIE_COLLECTOR_HPP

#include <vector>

#include "unit.hpp"
#include "event.hpp"
#include "map.hpp"


class ZombieCollector: public EventListener {
    std::vector<Unit *> _units {};

public:
    virtual void
    handle(Event *e) override
    {
        if (auto *ee = dynamic_cast<events::Forwarded *>(e)) {
            return handle(ee->event());
        }
        if (auto *ee = dynamic_cast<events::UnitDeath *>(e)) {
            _units.push_back(ee->unit());
        }
    }

    void
    collect(Map *m)
    {
        for (auto *unit: _units) {
            delete m->removeUnitAt(unit->position());
        }
        _units.clear();
    }
};

#endif
