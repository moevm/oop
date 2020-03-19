#ifndef NEUTRALOBJECT_H
#define NEUTRALOBJECT_H

#include <qglobal.h>

#include "Unit/FlyingUnit/dragon.h"
#include "Unit/FlyingUnit/kamikadze.h"

#include "Unit/GroundUnit/thief.h"
#include "Unit/GroundUnit/warrior.h"

#include "Strategy/nostrategy.h"
#include "Strategy/killstrategy.h"
#include "Strategy/dragonarmorupstrategy.h"
#include "Strategy/kamikadzearmorupstrategy.h"
#include "Strategy/thiefarmorupstrategy.h"
#include "Strategy/warriorarmorupstrategy.h"
#include "Strategy/healerstrategy.h"


class NeutralObject
{
public:
    virtual ~NeutralObject() = default;

    virtual std::shared_ptr<NeutralObject> clone() const = 0;

    virtual void operator[](std::shared_ptr<unit::Unit> unit);

protected:
    virtual void selectStrategy(std::shared_ptr<unit::Unit> unit) = 0;

protected:
    std::shared_ptr<Strategy> strategy;
};

#endif // NEUTRALOBJECT_H
