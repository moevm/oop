#ifndef NEUTRALOBJECT_H
#define NEUTRALOBJECT_H

#include "IDrawable.h"

#include "Unit/unit.h"

#include "Strategy/strategy.h"


class NeutralObject : public IDrawable
{
public:
    virtual ~NeutralObject() = default;

    Unit* operator()(Unit* unit);

    virtual NeutralObject* clone() = 0;

protected:
    virtual void selectStrategy(Unit* unit) = 0;

protected:
    Strategy* strategy;
};

#endif // NEUTRALOBJECT_H
