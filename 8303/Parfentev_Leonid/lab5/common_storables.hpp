#ifndef _H_COMMON_STORABLES_HPP
#define _H_COMMON_STORABLES_HPP

#include "storable.hpp"
#include "object_print.hpp"


class StorableEnd: public Storable {
    TRIVIALLY_STORABLE("end");
};

class StorableCoordinates: public Storable {
    Vec2 _c;

public:
    StorableCoordinates() {}

    StorableCoordinates(Vec2 c) :_c{c} {}

    virtual void
    store(std::ostream &os) const override
    {
        os << "coords " << _c.x() << " " << _c.y() << "\n";
    }

    virtual bool
    restore(std::istream &is,
            RestorerTable *) override
    {
        int x, y;
        is >> x >> y;
        _c = Vec2{x, y};
        return !is.fail();
    }

    Vec2 coords() const { return _c; }
};

class StorableWithIndex: public Storable {
    int _i;
    Storable *_s;

public:
    StorableWithIndex() {}

    StorableWithIndex(int idx, Storable *s)
        :_i{idx}, _s{s} {}

    virtual void
    store(std::ostream &os) const override
    {
        os << "index " << _i << " ";
        _s->store(os);
    }

    virtual bool
    restore(std::istream &is,
            RestorerTable *tab) override
    {
        is >> _i;
        _s = tab->restore(is);
        return !is.fail() && _s;
    }

    int index() const { return _i; }
    Storable *child() const { return _s; }

    static void
    storeWithIndex(int idx, const Storable *s,
                   std::ostream &os)
    {
        os << "index " << idx << " ";
        s->store(os);
    }
};

class StorableWithCoords: public Storable {
    Vec2 _c;
    Storable *_s;

public:
    StorableWithCoords() {}

    StorableWithCoords(Vec2 c, Storable *s)
        :_c{c}, _s{s} {}

    virtual void
    store(std::ostream &os) const override
    {
        os << "at " << _c.x() << " " << _c.y() << " ";
        _s->store(os);
    }

    virtual bool
    restore(std::istream &is,
            RestorerTable *tab) override
    {
        int x, y;
        is >> x >> y;
        _c = Vec2{x, y};
        _s = tab->restore(is);
        return !is.fail() && _s;
    }

    Vec2 coords() const { return _c; }
    Storable *child() const { return _s; }

    static void
    storeWithCoords(Vec2 pt, const Storable *s,
                    std::ostream &os)
    {
        os << "at " << pt.x() << " " << pt.y() << " ";
        s->store(os);
    }
};

#endif
