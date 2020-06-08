#ifndef ABSTRACTUNITFACTORY_H
#define ABSTRACTUNITFACTORY_H

#include "game_elements/team.h"

class Melee;
class Range;
class Nuker;

class BattleUnitFactory
{
protected:
    Team team;

public:
    virtual ~BattleUnitFactory(){}
    BattleUnitFactory(Team team):
        team(team)
    {};
    virtual Melee* createMelee(int x_pos, int y_pos) = 0;
    virtual Range* createRange(int x_pos, int y_pos) = 0;
    virtual Nuker* createNuker(int x_pos, int y_pos) = 0;
};

#endif // ABSTRACTUNITFACTORY_H
