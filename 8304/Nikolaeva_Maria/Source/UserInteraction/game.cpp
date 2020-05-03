#include "game.h"


Game::Game()
{
    playerUnits = new std::set<Unit* >;
    enemyUnits = new std::set<Unit* >;
}


void Game::run()
{
    init();

    isRun = true;
    while (isRun) {
        auto command = input();
        logic(command);
        enemyLogic();

        if (playerBase->getHealth() <= 0) {
            std::cout << "GAMEOVER. ENEMY WON(\n";
            return;
        }
        else if (enemyBase->getHealth() <= 0) {
            std::cout << "GAMEOVER. YOU WON!!!\n";
            return;
        }

        std::set<Unit* > tmp;
        for (auto i : *playerUnits) {
            if (i->getHealth() <= 0) {
                tmp.insert(i);
            }
        }

        for (auto i : tmp) {
            playerUnits->erase(i);
            this->playerBase->update();
            gameField->deleteUnit(i);
            delete i;
        }

        tmp.clear();
        for (auto i : *enemyUnits) {
            if (i->getHealth() <= 0) {
                tmp.insert(i);
            }
        }

        for (auto i : tmp) {
            enemyUnits->erase(i);
            this->enemyBase->update();
            gameField->deleteUnit(i);
            delete i;
        }

        draw();

        srand(time(0));
        auto j = rand() % (gameField->getHeight());
        auto i = rand() % 24;

        if (!(j % 4  == 0)) {
            gameField->getCell(j, i)->addNeutralObject(new KillerObject);
        }

        if (!(j % 7 == 0)) {
            gameField->getCell(j, i)->addNeutralObject(new HeallerObject);
        }

        Sleep(200);
    }
}


void Game::init()
{
    this->enemyBaseGold = 0;
    this->playerBaseGold = 0;
    isPlayerAttack = false;

    createField();
    mediator = new Mediator(gameField);

    playerBase = new Base(new Point2D(1, gameField->getHeight()/2),
                          mediator, PLAYER::ONE);

    enemyBase = new Base(new Point2D(gameField->getWidth() - 2,
                                     gameField->getHeight()/2), mediator, PLAYER::TWO);

    gameField->addUnit(playerBase);
    gameField->addUnit(enemyBase);

    playerUnits->insert(playerBase);
    enemyUnits->insert(enemyBase);

    playerFacade = new Facade (mediator, playerBase, playerUnits,
                               enemyBase, gameField);
    enemyFacade = new Facade (mediator, enemyBase, enemyUnits,
                              playerBase, gameField);

    std::cout << ". - grass\n~ - fog\n, - spines\n+ - heal\nx - bomb\nB- base\n";

    std::cout << "H - harpy\nD - dragon\nA - archer\nG - dwarf\nL - liveShield\nS - swordsman\n";

    Sleep(5000);
}


void Game::createField()
{
    gameField = new GameField(25, 35);

    auto spines = new SpinesLandscape;
    auto fog = new FogLandscape;
    auto proxy = new ProxyLandscape(spines);

    gameField->getCell(0, 0)->addLandscape(spines);

    for (size_t i = 0; static_cast<long long>(i) < gameField->getHeight(); ++i) {
        gameField->getCell(0, i)->addLandscape(proxy);
        gameField->getCell(gameField->getWidth() - 1, i)->addLandscape(proxy);
    }

    for (size_t i = 0; static_cast<long long>(i) < gameField->getWidth(); ++i) {
        gameField->getCell(i, 0)->addLandscape(proxy);
        gameField->getCell(i, gameField->getHeight() - 1)->addLandscape(proxy);
    }

    proxy = new ProxyLandscape(fog);

    for (size_t i = 0; static_cast<long long>(i) < gameField->getHeight(); ++i) {
        if (abs(static_cast<long long>(i) -
                static_cast<long long>(gameField->getHeight() / 4)) >= 2 &&
                abs(static_cast<long long>(i) -
                    static_cast<long long>(3 * gameField->getHeight() / 4)) >= 2) {
            gameField->getCell(gameField->getWidth()/2 - 2, i)->addLandscape(proxy);
            gameField->getCell(gameField->getWidth()/2 + 2, i)->addLandscape(proxy);
            gameField->getCell(gameField->getWidth()/2 - 1, i)->addLandscape(proxy);
            gameField->getCell(gameField->getWidth()/2 + 1, i)->addLandscape(proxy);
            gameField->getCell(gameField->getWidth()/2, i)->addLandscape(proxy);

        }
    }

}


void Game::draw() const
{
    std::string res;
    for (size_t i = 0; static_cast<long long>(i) < gameField->getHeight(); ++i) {
        for (size_t  j = 0; static_cast<long long>(j) < gameField->getWidth(); ++j) {
            auto cell = gameField->getCell(j, i);

            if (cell->isEmpty()) {
                auto& object = *cell->getNeutralObject();
                auto landscape = cell->getlandscape();
                if (typeid (object) != typeid(NoObject)) {
                    res += object.draw();
                }
                else {
                    res += landscape->draw();
                }
            }
            else {
                res += cell->getUnit()->draw();
            }
            res += ' ';
        }
        res += '\n';
    }

    res += "PlayerGold: " + std::to_string(playerBaseGold) +
            "    EnemyGold: " + std::to_string(enemyBaseGold) + "\n";
    res += "PlayerBase HP: " + std::to_string(playerBase->getHealth()) +
            "    EnemyBase HP : " + std::to_string(enemyBase->getHealth()) + "\n";

    res += "q - quit, a - attack, d - defense\n1 - "
           "create standing unit, 2 - ground, 3 - flying\n";

    system("cls");
    std::cout << res;
}


void Game::farmEnemy()
{
    enemyBaseGold += 10;
}


void Game::farmPlayer()
{
    playerBaseGold += 10;
}


void Game::logic(COMMAND command)
{
    farmPlayer();

    switch (command) {
    case COMMAND::ATTACK:
        isPlayerAttack = true;
        break;
    case COMMAND::DEFFEND:
        isPlayerAttack = false;
        break;
    case COMMAND::CRT_FLYING:
        if (playerBaseGold > 220) {
            auto isCreate = playerFacade->createFlyingUnit();
            if (isCreate) {
                playerBaseGold -= 220;
            }
        }
        break;
    case COMMAND::CRT_GROUND:
        if (playerBaseGold > 150) {
            auto isCreate = playerFacade->createInfantryUnit();
            if (isCreate) {
                playerBaseGold -= 150;
            }
        }
        break;
    case COMMAND::CRT_STANDING:
        if (playerBaseGold > 50) {
            auto isCreate = playerFacade->createStandingUnit();
            if (isCreate) {
                playerBaseGold -= 50;
            }
        }
        break;
    case COMMAND::EXIT:
        isRun = false;
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


void Game::enemyLogic()
{
    farmEnemy();
    enemyFacade->charge();

    srand(time(0));
    auto choose = rand() % 2;

    if (choose == 1) {
        choose = rand() % 3;
        switch (choose) {
        case 0:
            if (enemyBaseGold > 150) {
                auto isCreate = enemyFacade->createInfantryUnit();
                if (isCreate) {
                    enemyBaseGold -= 150;
                }
            }
            break;
        case 1:
            if (enemyBaseGold > 220) {
                auto isCreate = enemyFacade->createFlyingUnit();
                if (isCreate) {
                    enemyBaseGold -= 220;
                }
            }
        }
    }
}


COMMAND Game::input()
{
    if (kbhit()) {
        switch (getch()) {
        case 'a':
            return COMMAND::ATTACK;
        case 'd':
            return COMMAND::DEFFEND;
        case '1':
            return COMMAND::CRT_STANDING;
        case '2':
            return COMMAND::CRT_GROUND;
        case '3':
            return COMMAND::CRT_FLYING;
        case 'q':
            return COMMAND::EXIT;
        }
    }
    return COMMAND::NO_COMMAND;
}
