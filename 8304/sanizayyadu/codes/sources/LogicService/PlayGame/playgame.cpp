#include "playgame.hpp"


PlayGame::PlayGame()
{
    playerUnits = std::make_shared<std::set<std::shared_ptr<Unit>>>();
    enemyUnits = std::make_shared<std::set<std::shared_ptr<Unit>>>();
    proxyLog = std::make_shared<Proxy>(true,false);
    originator = std::make_shared<Originator>("/Users/sourcecode/Documents/LabFolder/save1.txt");
    
    careTaker = std::make_shared<Caretaker>(originator);
    
    numberOfEnemiesAllowed = 0;
}

void PlayGame::startGame(){
    initiliaze();
    isRunning = true;
    while (isRunning) {
        auto action = input();
        bool commandCanContinue = actionLogic(action);
       if(commandCanContinue)
           enemyLogic();
        
        if (playerBase->getHealthPoints() <= 0) {
            proxyLog->logMessage("GAME OVER. ENEMY WON!");
            std::cout << "ENEMY WON!\n";
            return;
        }
        else if (enemyBase->getHealthPoints() <= 0) {
            proxyLog->logMessage("GAME OVER. You WON!");
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
            proxyLog->logMessage(UnitLog::dieMessage(i));
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
            proxyLog->logMessage(UnitLog::dieMessage(i));
            enemyUnits->erase(i);
            i->notifyObservers();
            battleField->deleteUnit(i);
        }

        printGame();


    }
}

void PlayGame::initiliaze()
{
    proxyLog->logMessage("START GAME");

    std::cout << "SYMBOLS:\na - armor\n. - plains\n+ - heal\n* - desert\nO - oceans\n"
    "! - poison\nB- base\n";

    playerUnits->clear();
    enemyUnits->clear();
    
    isPlayerAttack = false;
    createBattleField();
    mediator = std::make_shared<Mediator>(battleField,proxyLog);

    playerBase =
    std::make_shared<Base>(Position2D(1,battleField->getHeight()/2),mediator,PLAYER::ONE);

    enemyBase = std::make_shared<Base>(Position2D(battleField->getWidth() - 2,
                                                 battleField->getHeight()/2), mediator,PLAYER::TWO);

    battleField->addUnit(playerBase);
    battleField->addUnit(enemyBase);
    
    proxyLog->logMessage(UnitLog::createMessage(playerBase));
    proxyLog->logMessage(UnitLog::createMessage(enemyBase));
    proxyLog->logMessage(PlayerLog::attack(PLAYER::TWO));
    proxyLog->logMessage(PlayerLog::deffend(PLAYER::ONE));


    playerFacade = std::make_shared<Facade>(mediator, playerBase, playerUnits,enemyBase, battleField,proxyLog);
    enemyFacade = std::make_shared<Facade>(mediator, enemyBase, enemyUnits,playerBase, battleField,proxyLog);
    
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
    
//    for (int i = 0; static_cast<long long>(i) < battleField->getHeight(); ++i) {
//    if (abs(static_cast<long long>(i) -
//            static_cast<long long>(battleField->getHeight() / 4)) >= 2 &&
//            abs(static_cast<long long>(i) -
//                static_cast<long long>(3 * battleField->getHeight() / 4)) >= 2) {
//        battleField->getFieldCell(Position2D(battleField->getWidth()/2 - 2, i))->setLandscape(proxy);
//        battleField->getFieldCell(Position2D(battleField->getWidth()/2 + 2, i))->setLandscape(proxy);
//        battleField->getFieldCell(Position2D(battleField->getWidth()/2 - 1, i))->setLandscape(proxy);
//        battleField->getFieldCell(Position2D(battleField->getWidth()/2 + 1, i))->setLandscape(proxy);
//        battleField->getFieldCell(Position2D(battleField->getWidth()/2, i))->setLandscape(proxy);
//
//    }
//    }
    

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
           "a - attack, d - defense,s - save game, l - load game\n";
    
    std::cout << res;
}

void PlayGame::enemyLogic()
{
    enemyFacade->charge();
    
    if(numberOfEnemiesAllowed < 4){
        numberOfEnemiesAllowed++;
        auto choose = rand() % 4;
           proxyLog->logMessage(PlayerLog::createUnit(true, PLAYER::TWO));
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

bool PlayGame::actionLogic(ACTION action)
{
    
    switch (action) {
        case ACTION::ATTACK:{
            proxyLog->logMessage(PlayerLog::attack(PLAYER::ONE));
            isPlayerAttack = true;
            break;
        }
        case ACTION::DEFFEND:{
            proxyLog->logMessage(PlayerLog::attack(PLAYER::ONE));
            isPlayerAttack = false;
            break;
        }
        case ACTION::SAVE:{
            std::cout << "Saving Game . . . . . . . .!\n";
            std::cout << "GAME SAVED!\n";
            careTaker->Backup(*this);
            return false;
            break;
        }
        case ACTION::LOAD:{
            std::cout << "Loading Game . . . . . . . .!\n";
            std::cout << "GAME LOADED SUCCESSFULLY!\n";
            careTaker->Undo(*this);
            return false;
            break;
        }
        case ACTION::CREATE_SHORTRANGE:{
            proxyLog->logMessage(PlayerLog::createUnit(true, PLAYER::ONE));
            playerFacade->createShortRangeUnit();
            break;
        }
        case ACTION::CREATE_LONGRANGE:{
            proxyLog->logMessage(PlayerLog::createUnit(true, PLAYER::ONE));
            playerFacade->createLongRangeUnit();
            break;
        }
        case ACTION::CREATE_DYNAMICRANGE:{
            proxyLog->logMessage(PlayerLog::createUnit(true, PLAYER::ONE));
            playerFacade->createDynamicRangeUnit();
            break;
        }
        case ACTION::EXIT:{
            proxyLog->logMessage("GAME OVER");
            isRunning = false;
            return false;
        }
    default:
        break;
    }
    
    if (isPlayerAttack) {
        playerFacade->charge();
    }
    else {
        playerFacade->deffend();
    }

    return true;
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
            case 's':
                return ACTION::SAVE;
            case 'l':
                return ACTION::LOAD;
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
