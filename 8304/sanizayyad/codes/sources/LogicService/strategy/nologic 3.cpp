#include "nologic.hpp"

void NoLogic::updateUnit(std::shared_ptr<Unit> unit) const
{
//    Q_UNUSED(unit);
}


std::shared_ptr<StrategyPattern> NoLogic::clone() const
{
    std::unique_ptr<StrategyPattern> strategy(new NoLogic);
    
    return strategy;
}
