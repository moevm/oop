#ifndef _STORABLE_HPP
#define _STORABLE_HPP

#include <iostream>
#include <map>
#include <string>
#include <utility>


class RestorerTable;

class Storable {
public:
    virtual void store(std::ostream &os) const =0;
    virtual bool restore(std::istream &,
                         RestorerTable *) { return true; };

    virtual ~Storable() {}
};

#define TRIVIALLY_STORABLE(keyword)             \
    public:                                     \
    virtual void                                \
    store(std::ostream &os) const override      \
    {                                           \
        os << keyword "\n";                     \
    }



class Restorer {
public:
    virtual Storable *restore(std::istream &is,
                              RestorerTable *tab) const =0;
};

class RestorerTable {
    std::map<std::string, Restorer *> _tab;

public:
    RestorerTable(std::map<std::string, Restorer *> m)
        :_tab{std::move(m)} {}

    Storable *
    restore(std::istream &is)
    {
        std::string n;
        is >> n;

        auto iter = _tab.find(n);
        if (iter == _tab.end()) {
            return nullptr;
        }

        Storable *s = iter->second->restore(is, this);
        if (!s) {
            return nullptr;
        }

        if (!s->restore(is, this)) {
            delete s;
            return nullptr;
        }
        return s;
    }

    static RestorerTable *defaultTable();
};

#endif
