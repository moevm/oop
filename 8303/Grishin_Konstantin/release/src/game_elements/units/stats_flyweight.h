#ifndef STATSFLYWEIGHT_H
#define STATSFLYWEIGHT_H

#include <vector>
#include "game_elements/units/unit_stats.h"

class StatsFlyweight
{
    static StatsFlyweight *instance;
    std::vector<UnitStats*> stats;
    StatsFlyweight(){};

    StatsFlyweight(const StatsFlyweight&) = delete;
    StatsFlyweight& operator=(const StatsFlyweight&) = delete;

public:
    static StatsFlyweight& getInstance();
    static void reset();
    const UnitStats& createStats(float maxHealth = 0,
                          float maxSteps = 0,
                          float baseDamage = 0,
                          int attackRadius = 0,
                          int blindZone = 0);
};


#endif // STATSFLYWEIGHT_H
