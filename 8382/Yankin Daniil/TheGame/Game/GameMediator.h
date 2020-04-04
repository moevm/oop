#pragma once

#include "Field/Field.h"

class Game;
class Landscape;
class IUnit;
class Base;


class GameMediator
{
    friend class Game;

public:
    bool unitMove(IUnit* unit, Point point);
    bool unitNeutralInterraction(IUnit* unit);
    void unitAttack(IUnit* attacker, IUnit* defender);
    void unitAttack(IUnit* attacker, Base* defender);
    bool unitUnificationAccess(IUnit* active, IUnit* passive);
    bool baseProductionAccess(Base* base);

    ILandscape* getLandscape(Point point);

private:
    GameMediator(Game* game);

    bool checkNeighborPoint(Point one, Point supposeNeighbor);
    uint16_t distance(Point one, Point two);

    Game* game;
};
