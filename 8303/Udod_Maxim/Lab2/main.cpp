#include <iostream>
#include "GameField/GameField.h"
#include "Objects/Units/Archer/CrossBowMan.h"
#include "Objects/Base.h"
#include "Landscapes/Ocean.h"
#include "Objects/Neutrals/House.h"
#include "Landscapes/Desert.h"
#include "Landscapes/ZeroSpace.h"
#include "Objects/Units/Archer/BlockBowMan.h"

void example1(){

    GameField::init(3, 3);

    Base *base = new Base();
    GameField::getInstance()->addObject(base, 0, 0);

    FireMage *fireMage1 = base->createUnit<FireMage>(Point(0, 1));
    FireMage *fireMage2 = base->createUnit<FireMage>(Point(0, 2));

    std::cout << "FireMage1 Health: " << fireMage1->getHealth() << std::endl;
    std::cout << "FireMage2 Health: " << fireMage2->getHealth() << std::endl;

    fireMage1->attack(*fireMage2);

    std::cout << "FireMage1 Health: " << fireMage1->getHealth() << std::endl;
    std::cout << "FireMage2 Health: " << fireMage2->getHealth() << std::endl;

    std::cout << std::endl;
    for (auto obj : *GameField::getInstance()) {
        std::cout << obj << std::endl;
    }
    std::cout << std::endl;

    GameField::getInstance()->getCell(Point(1, 0))->setLandscape(new ZeroSpace());
    fireMage1->move(Point(1, 0));

    std::cout << "FireMage1 Health: " << fireMage1->getHealth() << std::endl;
    std::cout << "FireMage2 Health: " << fireMage2->getHealth() << std::endl;

    fireMage1->attack(*fireMage2);

    std::cout << "FireMage1 Health: " << fireMage1->getHealth() << std::endl;

}

void example2(){

    GameField::init(3, 3);

    Base *base = new Base();
    GameField::getInstance()->addObject(base, 0, 0);

    House *house = new House();
    GameField::getInstance()->addObject(house, 1, 0);

    BlockBowMan *archer = base->createUnit<BlockBowMan>(Point(0, 1));
    std::cout << "BlockBowMan Health: " << archer->getHealth() << std::endl;

    archer->move(Point(1, 0));
    std::cout << "BlockBowMan Health: " << archer->getHealth() << std::endl;

    std::cout << std::endl;
    for (auto obj : *GameField::getInstance()) {
        std::cout << obj << std::endl;
    }
    std::cout << std::endl;

}

void example3(){

    GameField::init(3, 3);

    Base *base = new Base();
    GameField::getInstance()->addObject(base, 0, 0);

    auto *fireMage = base->createUnit<FireMage>(Point(1, 0));

    GameField::getInstance()->getCell(Point(0, 1))->setLandscape(new Ocean());
    fireMage->move(Point(0, 1));

    auto *house = new House();
    GameField::getInstance()->getCell(Point(1, 1))->setObject(house);
    fireMage->move(Point(1, 1));

    std::cout << std::endl;
    for (auto obj : *GameField::getInstance()) {
        std::cout << obj << std::endl;
    }

}

int main() {

    example2();

    return 0;
}
