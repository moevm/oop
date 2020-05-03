#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <math.h>

#include "GameField/gamefield.h"

#include "NeutralObject/killerobject.h"
#include "NeutralObject/heallerobject.h"

#include "facade.h"

#include "Unit/base/base.h"


enum class COMMAND : int
{
    NO_COMMAND,
    CRT_GROUND,
    CRT_FLYING,
    CRT_STANDING,
    ATTACK,
    DEFFEND,
    EXIT,
};


class Game
{
public:
    explicit Game();
    void run();

private:
    void init();
    void createField();
    void draw() const;
    void farmEnemy();
    void farmPlayer();
    void logic(COMMAND command = COMMAND::NO_COMMAND);
    void enemyLogic();
    COMMAND input();

private:
    bool isRun;
    Mediator* mediator;
    GameField* gameField;
    std::set<Unit* >* playerUnits;
    std::set<Unit* >* enemyUnits;
    Base* playerBase;
    Base* enemyBase;
    Facade* enemyFacade;
    Facade* playerFacade;
    size_t playerBaseGold;
    size_t enemyBaseGold;
    bool isPlayerAttack;
};

#endif // GAME_H
