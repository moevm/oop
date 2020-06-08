#ifndef COMMONUNITFACTORY_H
#define COMMONUNITFACTORY_H

#include "game_elements/units/battle_unit_factory.h"

class CommonUnitFactory : public BattleUnitFactory
{
public:
    CommonUnitFactory(Team team);
    Melee* createMelee(int x_pos, int y_pos) override;
    Range* createRange(int x_pos, int y_pos) override;
    Nuker* createNuker(int x_pos, int y_pos) override;
};

#endif // COMMONUNITFACTORY_H
