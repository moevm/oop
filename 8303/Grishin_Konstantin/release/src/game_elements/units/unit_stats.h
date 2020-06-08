#ifndef UNITSTATS_H
#define UNITSTATS_H


struct UnitStats
{
    float maxHealth;
    float maxSteps;
    float baseDamage;
    int attackRadius;
    int blindZone;

private:
    friend class StatsFlyweight;

    UnitStats(float maxHealth,
              float maxSteps,
              float baseDamage,
              int attackRadius,
              int blindZone):
        maxHealth(maxHealth),
        maxSteps(maxSteps),
        baseDamage(baseDamage),
        attackRadius(attackRadius),
        blindZone(blindZone)
    {}

    UnitStats(const UnitStats&) = delete;
    UnitStats& operator=(const UnitStats&) = delete;
    bool operator!=(const UnitStats& other){
        if(maxHealth != other.maxHealth) return 1;
        if(maxSteps != other.maxSteps) return 1;
        if(baseDamage != other.baseDamage) return 1;
        if(attackRadius != other.attackRadius) return 1;
        if(blindZone != other.blindZone) return 1;
        return 0;
    }
    bool operator==(const UnitStats& other){
        return !(*this != other);
    }
};

#endif // UNITSTATS_H
