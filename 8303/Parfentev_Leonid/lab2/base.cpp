#include <map>
#include <string>
#include <vector>

#include "unit.hpp"
#include "unit_factory.hpp"
#include "event.hpp"
#include "base.hpp"


bool
Base::canCreateUnit(const std::string &key) const
{
    return _cs->canCreate(key);
}

Unit *
Base::createUnit(const std::string &key)
{
    if (unitsCount() == maxUnitsCount()) {
        return nullptr;
    }

    if (!_cs->canCreate(key)) {
        return nullptr;
    }

    Unit *u = _cs->create(key);

    if (addUnit(u) < 0) {
        delete u;
        return nullptr;
    }

    return u;
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
    // u->emit(new UnitAddedEvent {u});

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

    if (auto *ee = dynamic_cast<UnitDeathEvent *>(e)) {
        removeUnit(ee->unit());
    } else if (auto *ee = dynamic_cast<UnitLiveDeletedEvent *>(e)) {
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
