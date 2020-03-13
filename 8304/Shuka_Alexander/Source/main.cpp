#include <iostream>
#include <vector>
#include <string>

#include "game.h"
#include "Unit/base.h"

using namespace unit;


void printInfo() {
    std::cout << "\n? - random item\n. - road\n" <<
                 "+ - base\n* - fog\nx - spikes\n";
}


void printField(std::shared_ptr<GameField> gameField) {
    std::string res;

    for (size_t i = 0; i < gameField->getHeight(); ++i) {
        for (size_t  j = 0; j < gameField->getWidth(); ++j) {
            auto cell = gameField->getCell(Point2D(j, i));

            if (cell->isEmpty()) {
                auto& object = *cell->getNeutralObject();
                auto& landscape = *cell->getLandscape();
                if (typeid (object) != typeid(NoObject)) {
                    res += "? ";
                }
                else {
                    res += landscape.draw();
                    res += ' ';
                }
            }
            else {
                res += cell->getUnit()->draw();
                res += ' ';
            }
        }
        res += '\n';
    }

    std::cout << res;
}


void test1() {
    std::shared_ptr<GameField> gameField(new GameField(15, 20));
    std::shared_ptr<Mediator> mediator(new Mediator(gameField));
    UnitDirector director;

    Point2D point(0, 0);
    std::vector<std::shared_ptr<Unit>> units;
    for (int i = 0; i < 5; ++i) {
        units.push_back(director.createThief(point, mediator));
        point.x += i;
        point.y++;
    }

    for (auto i : units) {
        gameField->addUnit(i);
    }

    bool isRun = true;
    while (isRun) {
        if (units[0]->getHealthPoints() <= 0) {
            gameField->deleteUnit(units[0]);
            units.pop_back();
        }
        if ((units[0] && !units[0]->moveRight()) || !units[1]->moveBottom()) {
            isRun = false;
        }

        Sleep(150);
        system("cls");
        std::cout << "____TEST1_____ Unit + object\n\n";
        printField(gameField);
        printInfo();
    }
}


void test2() {
    std::shared_ptr<GameField> gameField(new GameField(15, 30));
    std::shared_ptr<Mediator> mediator(new Mediator(gameField));
    UnitDirector director;

    Point2D point(0, 0);
    std::vector<std::shared_ptr<Unit>> units;
    units.push_back(director.createDragon(point, mediator));
    point.y = gameField->getHeight() - 1;
    units.push_back(director.createThief(point, mediator));

    for (auto i : units) {
        gameField->addUnit(i);
    }

    for (size_t i = 2; i < gameField->getWidth(); ++i) {
        gameField->getCell(Point2D(i, gameField->getHeight() - 1))->
                setLandscape(std::make_shared<ProxyLandscape>(
                    std::make_shared<SpikesLandscape>()));
        gameField->getCell(Point2D(i, 0))->
                setLandscape(std::make_shared<ProxyLandscape>(
                    std::make_shared<SpikesLandscape>()));
    }
    gameField->getCell(Point2D(gameField->getWidth()/2 - 1, 0))->
            setLandscape(std::make_shared<ProxyLandscape>(
                std::make_shared<FogLandscape>()));
    gameField->getCell(Point2D(3, gameField->getHeight()-1))->
            setLandscape(std::make_shared<ProxyLandscape>(
                std::make_shared<FogLandscape>()));

    bool isRun = true;
    while (isRun) {
        if (units[1]->getHealthPoints() <= 0) {
            gameField->deleteUnit(units[1]);
            units.pop_back();
        }

        for (auto i : units) {
            if (!i->moveRight())
                isRun = false;
        }

        Sleep(150);
        system("cls");
        std::cout << "____TEST2_____ Unit + landscape\n\n";
        printField(gameField);
        printInfo();
    }
}


void test3() {
    std::shared_ptr<GameField> gameField(new GameField(15, 30));
    std::shared_ptr<Mediator> mediator(new Mediator(gameField));
    std::shared_ptr<Base> base(new Base(Point2D(1, gameField->getHeight()/2), mediator));
    gameField->addUnit(base);

    for (size_t i = 0; i < gameField->getWidth(); ++i) {
        gameField->getCell(Point2D(i, gameField->getHeight() - 1))->
                setLandscape(std::make_shared<ProxyLandscape>(
                    std::make_shared<SpikesLandscape>()));
    }

    std::set<std::shared_ptr<Unit>> buff;
    std::set<std::shared_ptr<Unit>> units;
    for (int i = 0; i < 100; ++i) {
        auto unit = base->createGroundUnit();

        if (unit) {
            units.insert(unit);
        }

        for (auto i : units) {
            if (i->getHealthPoints() <= 0) {
                buff.insert(i);
            }
            else {
                i->moveRight();
                i->moveBottom();
            }
        }

        for (auto i : buff) {
            i->notify();
            units.erase(i);
            gameField->deleteUnit(i);
        }

        Sleep(150);
        system("cls");
        std::cout << "____TEST3_____ Base\n\n";
        printField(gameField);
        printInfo();

        buff.clear();
    }
}


int main() {    
    test1();
    Sleep(1000);

    test2();
    Sleep(1000);

    test3();

    return 0;
}
