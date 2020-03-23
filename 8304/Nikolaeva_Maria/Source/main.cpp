#include <iostream>
#include "GameField/gamefield.h"

#include "Unit/swordsman.h"
#include "Unit/liveshield.h"
#include "Unit/dragon.h"

#include "Factory/unitfactory.h"
#include "Factory/liveshieldfactory.h"
#include "Factory/archerfactory.h"
#include "Factory/dragonfactory.h"

#include "NeutralObject/heallerobject.h"
#include "NeutralObject/killerobject.h"
#include "NeutralObject/updatearmorobject.h"

#include "Landscape/spineslandscape.h"

#include "Unit/base/base.h"

#include <vector>

#include <Windows.h>

#include <string>


void printField(GameField* field) {
 //   system("cls");
    std::cout << "\n";
    std::string buffer;

    for (int i = 0; i < field->getHeight(); ++i) {
        for (int j = 0; j < field->getWidth(); ++j) {
            if (field->getCell(j, i)->isEmpty()) {

                if(field->getCell(j, i)->getNeutralObject()->draw() != '\0'){
                    buffer += field->getCell(j, i)->getNeutralObject()->draw();
                } else {
                    buffer += field->getCell(j, i)->getlandscape()->draw();
                }
                buffer += ' ';
            }
            else {
                buffer += field->getCell(j, i)->getUnit()->draw();
                buffer += ' ';
            }
        }
        buffer += "\n";
    }

    std::cout << buffer << std::endl;
}


void testIt() {
    GameField gameField(5, 5);
    Mediator mediator(&gameField);
    LiveShield unit(&mediator);

    gameField.addUnit(&unit);

    for (auto it = gameField.getIterator(); it.hasNext(); ++it) {
        if ((*it).isEmpty()) {
            std::cout << ". ";
        }
        else {
            std::cout << "U ";
        }
    }
}


void testFactory() {
    GameField gameField(5, 5);
    Mediator mediator(&gameField);

    UnitFactory* factory = new LiveShieldFactory;
    Unit* unit = factory->createUnit(&mediator);
    gameField.addUnit(unit);
    delete  factory;
    factory = new ArcherFactory;
    unit = factory->createUnit(&mediator);
    unit->setCoordinate(new Point2D(1,1));
    gameField.addUnit(unit);

    printField(&gameField);
}


void testNeutralObject() {
    GameField gameField(15, 15);
    Mediator mediator(&gameField);

    UnitFactory* factory = new DragonFactory;
    Unit* dUnit = factory->createUnit(&mediator);
    gameField.addUnit(dUnit);
    delete  factory;
    gameField.getCell(0, 1)->addNeutralObject(new UpdateArmorObject);

    factory = new ArcherFactory;
    Unit* aUnit = factory->createUnit(&mediator);
    aUnit->setCoordinate(new Point2D(2, 2));
    gameField.addUnit(aUnit);
    delete factory;

    for (int j = 0; j < gameField.getWidth(); ++j) {
        gameField.getCell(j, 3)->addLandscape(new ProxyLandscape(new SpinesLandscape));
    }
    gameField.getCell(2, 4)->addNeutralObject(new HeallerObject);

    factory = new DwarfFactory;
    Unit* gUnit = factory->createUnit(&mediator);
    gUnit->setCoordinate(new Point2D(5,5));
    gameField.addUnit(gUnit);
    delete factory;
    gameField.getCell(5, 6)->addNeutralObject(new KillerObject);

    printField(&gameField);
    std::cout << "Archer has " <<
                 aUnit->getHealth() << " health points" << std::endl;
    std::cout << "Dwarf has " <<
                 gUnit->getHealth() << " health points" << std::endl;
    std::cout << "Dragon has noArmor" << std::endl;
    aUnit->move(0, 1);

    dUnit->move(0, 1);

    gUnit->move(0, 1);

    printField(&gameField);
    std::cout << "Archer has " <<
                 aUnit->getHealth() << " health points" << std::endl;

    aUnit->move(0, 1);
    printField(&gameField);
    std::cout << "Archer has " <<
                 aUnit->getHealth() << " health points" << std::endl;
    std::cout << "Dwarf has " <<
                 gUnit->getHealth() << " health points" << std::endl;

    if (typeid(*(dUnit->getArmor())) == typeid(LightArmor)){
        std::cout << "Dragon has light armor";
    }

}


void testLandscape() {
    GameField gameField(15, 15);
    Mediator mediator(&gameField);

    Base base(new Point2D(0, 7), &mediator);
    gameField.addUnit(&base);

    std::vector<Unit*> units;

    units.push_back(base.createInfantryUnit(1, 0));
    units.push_back(base.createFlyingUnit(10, 0));

    for (int j = 1; j < 10; ++j) {
        gameField.getCell(j, 8)->addLandscape(new ProxyLandscape(new SpinesLandscape));
    }
    for (int j = 10; j < gameField.getWidth(); ++j) {
        gameField.getCell(j, 8)->addLandscape(new ProxyLandscape(new FogLandscape));
    }

    units.push_back(base.createInfantryUnit(11, 0));
    units.push_back(base.createFlyingUnit(2, 0));

    printField(&gameField);

    std::cout << "first infantry unit has " <<
                 units[0]->getHealth() << " health points" << std::endl;
    std::cout << "first flying unit has " <<
                 units[1]->getHealth() << " health points" << std::endl;
    Sleep(5000);

    units[0]->move(0, 1);
    units[1]->move(0, 1);

    units[2]->move(0, 1);
    units[3]->move(0, 1);

    printField(&gameField);
    Sleep(1000);

    std::cout << "first infantry unit has " <<
                 units[0]->getHealth() << " health points" << std::endl;
    std::cout << "first flying unit has " <<
                 units[1]->getHealth() << " health points" << std::endl;

}


void testBase(){
    GameField gameField(20, 20);
    Mediator mediator(&gameField);

    Base base(new Point2D(0, 7), &mediator);
    gameField.addUnit(&base);

    std::vector<Unit*> units;

    units.push_back(base.createInfantryUnit(2, -4));
    units.push_back(base.createStandingUnit(2, -3));

    Unit* fUnit;
    for (int i = 0; i < 10; i++){
        fUnit = base.createFlyingUnit(2, i - 1);
        if (fUnit != nullptr){
            units.push_back(fUnit);
        }
        system("cls");
        printField(&gameField);
        Sleep(500);
    }

    system("cls");
    printField(&gameField);
    Sleep(500);

    for (int i = 0; i < 3; i++){
        gameField.deleteUnit(units.back());
        units.pop_back();
        base.update();

        system("cls");
        printField(&gameField);
        Sleep(500);
    }

    for (int i = 0; i < 10; i++){
        fUnit = base.createStandingUnit(2, i + 5);
        if (fUnit != nullptr){
            units.push_back(fUnit);
        }

        system("cls");
        printField(&gameField);
        Sleep(500);
    }

}


int main()
{
    testIt();

    testFactory();

    testLandscape();

    testNeutralObject();

    testBase();

    return 0;
}
