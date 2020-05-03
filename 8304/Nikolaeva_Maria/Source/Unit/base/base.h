#ifndef BASE_H
#define BASE_H

#include "Unit/unit.h"

#include "Factory/unitfactory.h"
#include "Factory/swordsmanfactory.h"
#include "Factory/archerfactory.h"
#include "Factory/dragonfactory.h"
#include "Factory/dwarffactory.h"
#include "Factory/harpyfactory.h"
#include "Factory/liveshieldfactory.h"

#include <time.h>

constexpr int MAX_NUMBER_OF_UNITS = 10;


class Base : public Unit
{
public:
    explicit Base(Point2D* point,
                  Mediator* mediator, PLAYER player);

    virtual bool isFlying() override;

    Unit* createInfantryUnit(int dx, int dy);
    Unit* createFlyingUnit(int dx, int dy);
    Unit* createStandingUnit(int dx, int dy);

    void update();
    size_t getNumberOfUnits();

    virtual void regeneration() override;

    bool move(int dx, int dy) override;

    virtual Unit* clone() override;

    virtual char draw() override;

private:
    int generateRandomNum(int end) const;

    Unit* createUnit(Unit* unit);

private:
    size_t numberOfUnits;
};

#endif // BASE_H


