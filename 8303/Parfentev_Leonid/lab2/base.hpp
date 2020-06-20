#ifndef _H_BASE_HPP
#define _H_BASE_HPP

#include <map>
#include <string>
#include <vector>

#include "placeable.hpp"
#include "event.hpp"
#include "unit.hpp"


class UnitCreationStrategy {
public:
    virtual bool canCreate(const std::string &key) const =0;
    virtual std::vector<std::string> keys() const =0;
    virtual Unit *create(const std::string &key) =0;

    virtual ~UnitCreationStrategy() {}
};

class Base: public Placeable,
            public EventForwarder {

    std::map<int, Unit *> _units {};
    int _next_idx = 0;
    int _max_count = -1;

    UnitCreationStrategy *_cs;

public:
    Base(UnitCreationStrategy *cs)
        :_cs{cs} {}

    bool
    canCreateUnit(const std::string &key) const;
    Unit *
    createUnit(const std::string &key);

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
        unitsIter operator++(int) { unitsIter x{_iter}; ++x; return x; }
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
