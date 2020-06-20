#ifndef _H_NEUTRAL_OBJECT_HPP
#define _H_NEUTRAL_OBJECT_HPP

#include "placeable.hpp"
#include "unit.hpp"
#include "map.hpp"
#include "mediator.hpp"


class NeutralObject: public Placeable {
public:
    virtual bool canUse(const Unit *) { return true; }
    virtual void onUse(Unit *u, Mediator *m) =0;

    // It’s the object’s job to determine whether it was used by the
    // leaving unit.
    virtual void onLeave(Unit *) {};

    virtual ~NeutralObject() {};
};

#endif
