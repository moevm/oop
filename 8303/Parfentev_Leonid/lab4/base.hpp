#ifndef _H_BASE_HPP
#define _H_BASE_HPP

#include <map>
#include <string>
#include <vector>

#include "placeable.hpp"
#include "event.hpp"
#include "unit.hpp"
#include "mediator.hpp"


class Base: public Placeable,
            public EventForwarder {

    std::map<int, Unit *> _units {};
    int _next_idx = 0;
    int _max_count = -1;

public:
    Base() {}

    bool
    canCreateUnit(const std::string &key) const;
    int
    createUnit(const std::string &key, Mediator *m);

    int
    unitsCount() const { return (int)_units.size(); }
    bool
    setMaxUnitsCount(int m);
    int
    maxUnitsCount() const { return _max_count; }

    int
    addUnit(Unit *u);
    void
    removeUnit(Unit *u);
    Unit *
    getUnitById(int id) const;

    class unitsIter {
        using real_iter_t = std::map<int, Unit *>::const_iterator;
        real_iter_t _iter;

    public:
        unitsIter(real_iter_t it)
            :_iter{it} {}

        int id() const { return _iter->first; }
        Unit *unit() const { return _iter->second; }
        unitsIter &operator++() { ++_iter; return *this; }
        unitsIter
        operator++(int)
        {
            unitsIter x{_iter};
            ++*this;
            return x;
        }
        bool
        operator==(const unitsIter &o) const
        {
            return _iter == o._iter;
        }
        bool
        operator!=(const unitsIter &o) const
        {
            return !(*this == o);
        }
    };

    unitsIter
    unitsBegin() const { return unitsIter{_units.begin()}; }
    unitsIter
    unitsEnd() const { return unitsIter{_units.end()}; }

    virtual void
    handle(Event *e) override;

    virtual ~Base() override;
};

#endif
