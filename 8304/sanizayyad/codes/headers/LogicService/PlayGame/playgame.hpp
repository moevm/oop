#ifndef playgame_hpp
#define playgame_hpp

#include "facade.hpp"
#include "base.hpp"
#include "BattleField.hpp"
#include "originator.hpp"
#include "caretaker.hpp"
#include "proxy.hpp"

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
    SAVE,
    LOAD,
    EXIT,
};


class PlayGame
{
    friend Originator;
public:
    explicit PlayGame();
    void startGame();

private:
    void initiliaze();
    void createBattleField();
    void printGame() const;
    void farmEnemy();
    void farmPlayer();
    bool actionLogic(ACTION action = ACTION::NO_ACTION);
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
    std::shared_ptr<Proxy> proxyLog;
    std::shared_ptr<Originator> originator;
    std::shared_ptr<Caretaker> careTaker;

    bool isPlayerAttack;
    int numberOfEnemiesAllowed;
};

#endif /* playgame_hpp */
