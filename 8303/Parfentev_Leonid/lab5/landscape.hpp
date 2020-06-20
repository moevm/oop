#ifndef _H_LANDSCAPE_HPP
#define _H_LANDSCAPE_HPP


#include "storable.hpp"

class Unit;

class Landscape: public Storable {
public:
    virtual void onEnter(Unit *u) =0;
    virtual void onLeave(Unit *u) =0;

    virtual ~Landscape() {}
};

namespace landscapes {

    class Normal: public Landscape {
    public:
        virtual void onEnter(Unit *) override {}
        virtual void onLeave(Unit *) override {}

        TRIVIALLY_STORABLE("l_normal");
    };

}

#endif
