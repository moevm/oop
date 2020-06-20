#ifndef _H_EVENT_PRINTER_HPP
#define _H_EVENT_PRINTER_HPP

#include <sstream>
#include <iostream>
#include <string>
#include <map>

#include "event.hpp"
#include "unit.hpp"
#include "base.hpp"
#include "player.hpp"
#include "object_print.hpp"


class EventPrinter: public EventListener {
    std::ostream *_os;
    bool _free_os;

    std::map<EventForwarder *, std::string> _prefix_map {};
    int _base_idx = 0;

    std::string
    makeName(const char *base, int idx)
    {
        std::ostringstream oss {};
        oss << base << " " << idx;
        return oss.str();
    }

public:
    EventPrinter(std::ostream &os)
        :_os{&os}, _free_os{false} {}

    EventPrinter(std::ostream *os)
        :_os{os}, _free_os{true} {}

    std::ostream &
    ostream() const { return *_os; }

    void
    setPrefix(EventForwarder *f, const std::string &s)
    {
        _prefix_map[f] = s;
    }

    virtual void
    handle(Event *e) override
    {
        if (auto *ee = dynamic_cast<events::Forwarded *>(e)) {
            auto iter = _prefix_map.find(ee->forwarder());
            if (iter != _prefix_map.end()) {
                (*_os) << iter->second << ": ";
            }

            return handle(ee->event());

        } else if (auto *ee =
                   dynamic_cast<events::UnitAdded *>(e)) {
            (*_os) << "Unit added: " << ee->unit() << "\n";

        } else if (auto *ee =
                   dynamic_cast<events::UnitDeath *>(e)) {
            (*_os) << "Unit died: " << ee->unit() << "\n";

        } else if (auto *ee =
                   dynamic_cast<events::UnitTakesDamage *>(e)) {
            (*_os) << "Unit " << ee->unit() << " takes "
                   << ee->damage() << " health points of damage\n";

        } else if (auto *ee =
                   dynamic_cast<events::UnitGetsHealed *>(e)) {
            (*_os) << "Unit " << ee->unit() << " gets healed by "
                   << ee->health() << " health points\n";

        } else if (auto *ee =
                   dynamic_cast<events::UnitAttacked *>(e)) {
            (*_os) << "Unit " << ee->attacker()
                   << " attacked another unit " << ee->target() << "\n";

        } else if (auto *ee =
                   dynamic_cast<events::UnitWasAttacked *>(e)) {
            (*_os) << "Unit " << ee->target()
                   << " was attacked by another unit "
                   << ee->attacker() << "\n";
        } else if (auto *ee =
                   dynamic_cast<events::UnitMoved *>(e)) {
            (*_os) << "Unit " << ee->unit()
                   << " moved from " << ee->sourcePos() << "\n";

        } else if (auto *ee =
                   dynamic_cast<events::UnitUsedObject *>(e)) {
            (*_os) << "Unit " << ee->unit()
                   << " used object " << ee->neutralObject() << "\n";

        } else if (auto *ee =
                   dynamic_cast<events::UnitLiveDeleted *>(e)) {
            (*_os) << "(Live unit " << ((void *)ee->unit())
                   << " deleted)\n";

        } else if (auto *ee =
                   dynamic_cast<events::BaseAdded *>(e)) {
            auto name = makeName("Base", ++_base_idx);
            setPrefix(ee->base(), name);
            (*_os) << "New base: " << name << "\n";

        } else if (auto *ee =
                   dynamic_cast<events::TurnStarted *>(e)) {
            (*_os) << "Turn of player "
                   << ee->player()->name() << "\n";

        } else if (auto *ee =
                   dynamic_cast<events::TurnOver *>(e)) {
            (*_os) << "Turn of player "
                   << ee->player()->name() << " over\n";

        } else {
            (*_os) << "Unknown event\n";
        }
    }

    virtual ~EventPrinter() override
    {
        if (_free_os) {
            _os->flush();
            delete _os;
        }
    }
};

#endif
