
#ifndef StrategyResArcher_hpp
#define StrategyResArcher_hpp

#include <stdio.h>
#include "../../Strategy.hpp"

class StrategyResArcher : public Strategy
{
public:
    double use() override;
};

#endif /* StrategyResArcher_hpp */