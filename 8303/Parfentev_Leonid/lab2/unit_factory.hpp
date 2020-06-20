#ifndef _H_UNIT_FACTORY_HPP
#define _H_UNIT_FACTORY_HPP

#include "unit.hpp"


class UnitFactory {
public:
    virtual Unit *create() const =0;

    virtual ~UnitFactory() {}
};

template<typename U>
class SimpleUnitFactory: public UnitFactory {
public:
    virtual Unit *
    create() const override
    {
        return new U {};
    }
};

#endif
