#ifndef _H_LANDSCAPE_HPP
#define _H_LANDSCAPE_HPP


class Unit;

class Landscape {
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
    };

}

#endif
