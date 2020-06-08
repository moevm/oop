#ifndef MAGICUNITFACTORY_H
#define MAGICUNITFACTORY_H

#include "game_elements/units/battle_unit_factory.h"

class MagicUnitFactory : public BattleUnitFactory
{
public:
    MagicUnitFactory(Team team);
    Melee* createMelee(int x_pos, int y_pos) override;
    Range* createRange(int x_pos, int y_pos) override;
    Nuker* createNuker(int x_pos, int y_pos) override;
};

#endif // MAGICUNITFACTORY_H
