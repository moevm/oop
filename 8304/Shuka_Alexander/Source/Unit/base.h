#ifndef BASE_H
#define BASE_H

#include <time.h>

#include "Unit/unit.h"

#include "UnitBuilder/unitdirector.h"

#include "IObserver/isubscriber.h"


class UnitSnapshot;


namespace  unit {
constexpr int MAX_N_UNITS = 10;

class Base : public Unit, public ISubscriber,
        public std::enable_shared_from_this<Base>
{
    friend class Snapshot;

public:
    explicit Base(const Point2D& point,
                  std::shared_ptr<Mediator> mediator,
                  PLAYER player, double healthPoints = 400);

    virtual bool moveLeft() override;
    virtual bool moveTop() override;
    virtual bool moveBottom() override;
    virtual bool moveRight() override;
    virtual bool isFly() const override;

    std::shared_ptr<Unit> createGroundUnit(int dx, int dy);
    std::shared_ptr<Unit> createFlyingUnit(int dx, int dy);
    std::shared_ptr<Unit> createStandingUnit(int dx, int dy);

    std::shared_ptr<Unit> createUnit(const UnitSnapshot& unitSnapshot);

    virtual size_t farm() const override;

    virtual std::shared_ptr<Unit> clone() override;

    virtual char draw() const override;

    virtual void update() override;

    size_t getNUnits() const;

private:
    int generateRandomNum(int end) const;

    std::shared_ptr<Unit> createUnit(std::shared_ptr<Unit> unit);

    void setHealthPoints(double healthPoints);

private:
    UnitDirector director;
    size_t nUnits;
};
}

#endif // BASE_H
