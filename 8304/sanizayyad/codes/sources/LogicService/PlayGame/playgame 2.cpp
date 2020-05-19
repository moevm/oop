#include "playgame.hpp"


PlayGame::PlayGame()
{
    playerUnits = std::make_shared<std::set<std::shared_ptr<Unit>>>();
    enemyUnits = std::make_shared<std::set<std::shared_ptr<Unit>>>();
    numberOfEnemiesAllowed = 0;
}

void PlayGame::startGame(){
    initiliaze();
    isRunning = true;
    while (isRunning) {
        auto action = input();
        actionLogic(action);
        
        enemyLogic();
        
        if (playerBase->getHealthPoints() <= 0) {
            std::cout << "ENEMY WON!\n";
            return;
        }
        else if (enemyBase->getHealthPoints() <= 0) {
            std::cout << "YOU WON!\n";
            return;
        }

        std::set<std::shared_ptr<Unit>> tmp;
        for (auto i : *playerUnits) {
            if (i->getHealthPoints() <= 0) {
                tmp.insert(i);
            }
        }

        for (auto i : tmp) {
            playerUnits->erase(i);
            i->notifyObservers();
            battleField->deleteUnit(i);
        }

        tmp.clear();
        for (auto i : *enemyUnits) {
            if (i->getHealthPoints() <= 0) {
                tmp.insert(i);
            }
        }

        for (auto i : tmp) {
            enemyUnits->erase(i);
            i->notifyObservers();
            battleField->deleteUnit(i);
        }

        printGame();


    }
}

void PlayGame::initiliaze()
{

    isPlayerAttack = false;

    createBattleField();
    mediator = std::make_shared<Mediator>(battleField);

    playerBase =
    std::make_shared<Base>(Position2D(1,battleField->getHeight()/2),mediator,PLAYER::ONE);

    enemyBase = std::make_shared<Base>(Position2D(battleField->getWidth() - 2,
                                                 battleField->getHeight()/2), mediator,PLAYER::TWO);

    battleField->addUnit(playerBase);
    battleField->addUnit(enemyBase);

    playerUnits->insert(playerBase);
    enemyUnits->insert(enemyBase);

    playerFacade = std::make_shared<Facade>(mediator, playerBase, playerUnits,enemyBase, battleField);
    enemyFacade = std::make_shared<Facade>(mediator, enemyBase, enemyUnits,playerBase, battleField);
    
    std::cout << "a - armor\n. - plains\n+ - heal\n* - desert\nO - oceans\n"
                 "! - poison\nB- base\n";
}

void PlayGame::createBattleField(){
    battleField = std::make_shared<BattleField>(19, 25);
    
    auto plains = std::make_shared<PlainsLandscape>();
    auto oceans = std::make_shared<OceansLandscape>();
    auto proxy = std::make_shared<ProxyLandscape>(plains);

    battleField->getFieldCell(Position2D(0, 0))->setLandscape(plains);

    for (int i = 0; i < battleField->getHeight(); ++i) {
        battleField->getFieldCell(Position2D(0, i))->setLandscape(proxy);
        battleField->getFieldCell(Position2D(battleField->getWidth() - 1, i))->setLandscape(proxy);
    }

    for (int i = 0; i < battleField->getWidth(); ++i) {
        battleField->getFieldCell(Position2D(i, 0))->setLandscape(proxy);
        battleField->getFieldCell(Position2D(i,battleField->getHeight() - 1))->setLandscape(proxy);
    }

    proxy = std::make_shared<ProxyLandscape>(oceans);
    
    for (int i = 0; static_cast<long long>(i) < battleField->getHeight(); ++i) {
    if (abs(static_cast<long long>(i) -
            static_cast<long long>(battleField->getHeight() / 4)) >= 2 &&
            abs(static_cast<long long>(i) -
                static_cast<long long>(3 * battleField->getHeight() / 4)) >= 2) {
        battleField->getFieldCell(Position2D(battleField->getWidth()/2 - 2, i))->setLandscape(proxy);
        battleField->getFieldCell(Position2D(battleField->getWidth()/2 + 2, i))->setLandscape(proxy);
        battleField->getFieldCell(Position2D(battleField->getWidth()/2 - 1, i))->setLandscape(proxy);
        battleField->getFieldCell(Position2D(battleField->getWidth()/2 + 1, i))->setLandscape(proxy);
        battleField->getFieldCell(Position2D(battleField->getWidth()/2, i))->setLandscape(proxy);

    }
    }
    
    

    auto healthObject = std::make_shared<HealthObject>();
    auto poison = std::make_shared<PoisonObject>();

    battleField->getFieldCell(Position2D(18,9))->setNeutralObject(poison);


    battleField->getFieldCell(Position2D(8,9))->setNeutralObject(healthObject);

    
    
}
void PlayGame::printGame() const{
    std::string res;
    for (int i = 0; i < battleField->getHeight(); ++i) {
        for (int  j = 0; j < battleField->getWidth(); ++j) {
            auto cell = battleField->getFieldCell(Position2D(j, i));
            if (cell->isEmpty()) {
                auto& object = *cell->getNeutralObject();
                auto& landscape = *cell->getLandscape();
                if (typeid (object) != typeid(NoObject)) {
                    res += object.draw();
                }
                else {
                    res += landscape.draw();
                }
            }
            else {
                res += cell->getUnit()->getUnitName()[0];
            }
            res += ' ';
        }
        res += '\n';
    }
    
    res += "Player Base HP: " + std::to_string(playerBase->getHealthPoints()) + "\n";
    res += "Enemey Base HP: " + std::to_string(enemyBase->getHealthPoints()) + "\n";

    res += "q - quit, 1 - short range, 2 - long range, 3 - dynamic range\n"
           "a - attack, d - defense\n";
    
    std::cout << res;
}

void PlayGame::actionLogic(ACTION action)
{
    
    switch (action) {
    case ACTION::ATTACK:
        isPlayerAttack = true;
        break;
    case ACTION::DEFFEND:
        isPlayerAttack = false;
        break;
    case ACTION::CREATE_SHORTRANGE:
        playerFacade->createShortRangeUnit();
        break;
    case ACTION::CREATE_LONGRANGE:
        playerFacade->createLongRangeUnit();
        break;
    case ACTION::CREATE_DYNAMICRANGE:
        playerFacade->createDynamicRangeUnit();
        break;
    case ACTION::EXIT:
        isRunning = false;
        break;
    default:
        break;
    }
    
    if (isPlayerAttack) {
        playerFacade->charge();
    }
    else {
        playerFacade->deffend();
    }
}



void PlayGame::enemyLogic()
{
    enemyFacade->charge();
    
    if(numberOfEnemiesAllowed < 4){
        numberOfEnemiesAllowed++;
        auto choose = rand() % 4;
           
           switch (choose) {
           case 1:
               enemyFacade->createShortRangeUnit();
               break;
           case 2:
               enemyFacade->createLongRangeUnit();
               break;
           case 3:
               enemyFacade->createDynamicRangeUnit();
               break;
           }
    }

    
}

ACTION PlayGame::input()
{
    
    if (true) {
        char ac;
        std::cin>>ac;
        switch (ac) {
        case 'a':
            return ACTION::ATTACK;
        case 'd':
            return ACTION::DEFFEND;
        case '1':
            return ACTION::CREATE_SHORTRANGE;
        case '2':
            return ACTION::CREATE_LONGRANGE;
        case '3':
            return ACTION::CREATE_DYNAMICRANGE;
        case 'q':
            return ACTION::EXIT;
        }
    }
    return ACTION::NO_ACTION;
}
