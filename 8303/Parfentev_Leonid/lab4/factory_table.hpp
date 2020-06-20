#ifndef _H_FACTORY_TABLE_HPP
#define _H_FACTORY_TABLE_HPP

#include <map>
#include <string>

#include "unit.hpp"
#include "melee_units.hpp"
#include "ranged_units.hpp"
#include "catapult_units.hpp"
#include "unit_factory.hpp"


class FactoryTable {
    std::map<std::string, UnitFactory *> _tab {};

    void
    registerFactory(const std::string &key, UnitFactory *f)
    {
        _tab[key] = f;
    }

    FactoryTable()
    {
#define REG(k, T)                                   \
        registerFactory(                            \
            k, new SimpleUnitFactory<units::T> {})
        REG("swordsman", Swordsman);
        REG("spearsman", Spearsman);
        REG("cavalry", Cavalry);
        REG("archer", Archer);
        REG("slinger", Slinger);
        REG("onager", Onager);
        REG("boltthrower", BoltThrower);
#undef REG
    }

public:
    static const FactoryTable *
    instance()
    {
        static FactoryTable *inst = new FactoryTable {};
        return inst;
    }

    virtual bool
    canCreate(const std::string &key) const
    {
        return _tab.find(key) != _tab.end();
    }

    virtual std::vector<std::string>
    keys() const
    {
        std::vector<std::string> keys {};
        for (auto p: _tab) {
            keys.push_back(p.first);
        }
        return keys;
    }

    virtual Unit *
    create(const std::string &key) const
    {
        auto iter = _tab.find(key);
        if (iter == _tab.end()) {
            return nullptr;
        }

        return iter->second->create();
    }

    ~FactoryTable()
    {
        for (auto p: _tab) {
            delete p.second;
        }
    }
};

#endif
