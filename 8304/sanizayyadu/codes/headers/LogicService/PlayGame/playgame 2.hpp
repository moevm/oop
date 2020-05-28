#ifndef playgame_hpp
#define playgame_hpp

#include "facade.hpp"
#include "base.hpp"
#include "BattleField.hpp"
#include "log.hpp"
#include "terminallog.hpp"
#include "filelog.hpp"
#include "unitlog.hpp"
#include "playerlog.hpp"


#include <math.h>
#include <iostream>
#include <stdio.h>

enum class ACTION : int
{
    NO_ACTION,
    CREATE_SHORTRANGE,
    CREATE_LONGRANGE,
    CREATE_DYNAMICRANGE,
    ATTACK,
    DEFFEND,
    EXIT,
};


class PlayGame
{
public:
    explicit PlayGame();
    void startGame();

private:
    void initiliaze();
    void createBattleField();
    void printGame() const;
    void farmEnemy();
    void farmPlayer();
    void actionLogic(ACTION action = ACTION::NO_ACTION);
    void enemyLogic();
    ACTION input();


private:
    bool isRunning;
    std::shared_ptr<Mediator> mediator;
    std::shared_ptr<BattleField> battleField;
    std::shared_ptr<std::set<std::shared_ptr<Unit>>> playerUnits;
    std::shared_ptr<std::set<std::shared_ptr<Unit>>> enemyUnits;
    std::shared_ptr<Base> playerBase;
    std::shared_ptr<Base> enemyBase;
    std::shared_ptr<Facade> enemyFacade;
    std::shared_ptr<Facade> playerFacade;
    std::shared_ptr<Log> log;
    bool isPlayerAttack;
    
    int numberOfEnemiesAllowed;
};

#endif /* playgame_hpp */
