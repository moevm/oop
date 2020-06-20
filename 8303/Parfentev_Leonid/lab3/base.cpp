#include <map>
#include <string>
#include <vector>

#include "unit.hpp"
#include "unit_factory.hpp"
#include "event.hpp"
#include "base.hpp"
#include "mediator.hpp"


bool
Base::canCreateUnit(const std::string &key) const
{
    if (unitsCount() == maxUnitsCount()) {
        return false;
    }

    if (!_cs->canCreate(key)) {
        return false;
    }

    return true;
}

int
Base::createUnit(const std::string &key, Mediator *m)
{
    if (!canCreateUnit(key)) {
        return -1;
    }

    if (m->infoAt(position()).unit()) {
        return false;
    }

    Unit *u = _cs->create(key);
    int id = addUnit(u);

    if (id < 0) {
        delete u;
        return -1;
    }

    if (!m->spawnUnit(u, position())) {
        removeUnit(u);
        delete u;
        return -1;
    }

    return id;
}

bool
Base::setMaxUnitsCount(int m)
{
    if (m < unitsCount()) {
        return false;
    }
    _max_count = m;
    return true;
}

int
Base::addUnit(Unit *u)
{
    if (maxUnitsCount() >= 0
        && unitsCount() == maxUnitsCount()) {
        return -1;
    }

    _units[_next_idx] = u;
    u->subscribe(this);
    u->emit(new events::UnitAdded {u});

    return _next_idx++;
}

void
Base::removeUnit(Unit *u)
{
    u->unsubscribe(this);

    for (auto iter = _units.begin();
         iter != _units.end();
         ++iter) {
        if (iter->second == u) {
            _units.erase(iter);
            break;
        }
    }
}

Unit *
Base::getUnitById(int id) const
{
    auto iter = _units.find(id);
    return (iter != _units.end())
        ? iter->second
        : nullptr;
}

void
Base::handle(Event *e)
{
    EventForwarder::handle(e);

    if (auto *ee = dynamic_cast<events::UnitDeath *>(e)) {
        removeUnit(ee->unit());
    } else if (auto *ee = dynamic_cast<events::UnitLiveDeleted *>(e)) {
        removeUnit(ee->unit());
    }
}

Base::~Base()
{
    for (auto p: _units) {
        p.second->unsubscribe(this);
    }
    delete _cs;
}
