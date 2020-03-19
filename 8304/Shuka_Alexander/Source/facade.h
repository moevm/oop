#ifndef FACADE_H
#define FACADE_H

#include "mediator.h"

#include "Field/gamefield.h"

#include "Unit/unit.h"
#include "Unit/base.h"


class Facade
{
public:
    Facade(std::shared_ptr<Mediator> mediator, std::shared_ptr<unit::Base> base,
           std::shared_ptr<std::set<std::shared_ptr<unit::Unit>>> units,
           std::shared_ptr<unit::Base> enemyBase,
           std::shared_ptr<GameField> field);

    void charge();
    void deffend();
    bool createGroundUnit();
    bool createStandingUnit();
    bool createFlyingUnit();

protected:
    bool attack(std::shared_ptr<unit::Unit> unit);
    void moveUnit(std::shared_ptr<unit::Unit> unit);

private:
    std::shared_ptr<unit::Base> base;
    std::shared_ptr<unit::Base> enemyBase;
    std::shared_ptr<std::set<std::shared_ptr<unit::Unit>>> units;
    std::shared_ptr<Mediator> mediator;
    std::shared_ptr<GameField> field;
};

#endif // FACADE_H
