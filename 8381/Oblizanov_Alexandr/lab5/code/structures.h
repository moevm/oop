#ifndef STRUCTURES_H
#define STRUCTURES_H

#include "libraries.h"
#include "skills.h"

struct UnitParameters
{
    UnitType type;
    unsigned x;
    unsigned y;
    int move;
    int power;
    int spread;
    int charactBonus;
    int attackBonus;
    int securityBonus;
};

struct NeutralParameters
{
    NeutralParameters(NeutralType type, unsigned x, unsigned y)
        : type(type), x(x), y(y) {}
    NeutralParameters() {}
    NeutralType type;
    unsigned x;
    unsigned y;
};

struct BaseParameters
{
    unsigned number;
    unsigned stability;
    unsigned limit;
    unsigned x;
    unsigned y;
    std::vector<UnitParameters> units;
};

struct GameParameters
{
    GameParameters(unsigned width, unsigned height, unsigned itemLimit, unsigned itemCounter, size_t baseCount)
        : width(width), height(height), itemLimit(itemLimit), itemCounter(itemCounter), baseCount(baseCount) {}
    GameParameters() {}
    unsigned width;
    unsigned height;
    unsigned itemLimit;
    unsigned itemCounter;
    std::vector<LandType> landscape;
    size_t baseCount;
    std::vector<BaseParameters> bases;
    std::vector<NeutralParameters> neutrals;
};

#endif // STRUCTURES_H
