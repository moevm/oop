
#ifndef ResourceGenerator_hpp
#define ResourceGenerator_hpp

#include <stdio.h>
#include "../NeutralObject.hpp"
#include "../../combatObject/unit/Unit.hpp"
#include "../../../strategy/Strategy.hpp"
#include "../../../strategy/varietyStrategy/strategyResArcher/StrategyResArcher.hpp"
#include "../../../strategy/varietyStrategy/strategyResCavalry/StrategyResCavalry.hpp"
#include "../../../strategy/varietyStrategy/strategyResInfantry/StrategyResInfantry.hpp"
#include "../../../strategy/Context.hpp"

class ResourceGenerator : public NeutralObject, public Context
{
protected:
    unsigned int resType;
    double resPerStep;
    double coefficient;

    void useStrategy() override;
    void setStrategy(Strategy *strategy) override;

public:
    ResourceGenerator();
    ~ResourceGenerator();
    void operator+(Object *object) override;
    void setCoefficient(double coefficient);
    void setPlayerID(std::string playerID);
    unsigned int getResType();
    double getResPerStep();
    double getCoefficient();
    double getResPerStepForUnit();
    bool isMoveable() override;
    v8::Local<v8::Object> getFullInfo();
};

#endif /* ResourceGenerator_hpp */