
#ifndef StrategyResInfantry_hpp
#define StrategyResInfantry_hpp

#include <stdio.h>
#include "../../Strategy.hpp"

class StrategyResInfantry : public Strategy
{
public:
    double use() override;
};

#endif /* StrategyResInfantry_hpp */