
#ifndef StrategyResCavalry_hpp
#define StrategyResCavalry_hpp

#include <stdio.h>
#include "../../Strategy.hpp"

class StrategyResCavalry : public Strategy
{
public:
    double use() override;
};

#endif /* StrategyResCavalry_hpp */