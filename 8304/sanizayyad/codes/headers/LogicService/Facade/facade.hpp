#ifndef facade_hpp
#define facade_hpp

#include "unit.hpp"
#include "mediator.hpp"
#include "base.hpp"
#include "BattleField.hpp"
#include "log.hpp"
#include "unitlog.hpp"

#include <math.h>

#include <stdio.h>


class Facade
{
public:
    Facade(std::shared_ptr<Mediator> mediator, std::shared_ptr<Base> homeBase,
           std::shared_ptr<std::set<std::shared_ptr<Unit>>> units,
           std::shared_ptr<Base> enemyBase,
           std::shared_ptr<BattleField> battleField,
           std::shared_ptr<Log> log);

    void charge();
    void deffend();
    
    bool createShortRangeUnit();
    bool createLongRangeUnit();
    bool createDynamicRangeUnit();
    

protected:
    bool attack(std::shared_ptr<Unit> unit);
    void moveUnit(std::shared_ptr<Unit> unit);
    std::shared_ptr<Unit> createUnit(std::string type);


private:
    std::shared_ptr<Base> homeBase;
    std::shared_ptr<Base> enemyBase;
    std::shared_ptr<std::set<std::shared_ptr<Unit>>> units;
    std::shared_ptr<Mediator> mediator;
    std::shared_ptr<BattleField> battleField;
    std::shared_ptr<Log> log;
};


#endif /* facade_hpp */
