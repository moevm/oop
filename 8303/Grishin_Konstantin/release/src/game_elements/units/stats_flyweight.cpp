#include "stats_flyweight.h"

StatsFlyweight* StatsFlyweight::instance = nullptr;
StatsFlyweight& StatsFlyweight::getInstance(){
    if(instance == nullptr)
        instance = new StatsFlyweight;
    return *instance;
}


void StatsFlyweight::reset(){
    if(instance){
        for(auto s: instance->stats){
            delete s;
        }
    }
    delete instance;
    instance = nullptr;
}

const UnitStats& StatsFlyweight::createStats(float maxHealth,
                                       float maxSteps,
                                       float baseDamage,
                                       int attackRadius,
                                       int blindZone)
{
    auto new_s = new UnitStats{maxHealth, maxSteps, baseDamage, attackRadius, blindZone};
    for(auto s: stats){
        if(s == new_s){
            delete new_s;
            return *s;
        }
    }
    stats.push_back(new_s);
    return *new_s;
}
