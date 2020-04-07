#include <iostream>
#include <memory>
#include <vector>

#include "unitcreator.hpp"
#include "BattleField.hpp"
#include "battlefielditerator.hpp"
#include "mediator.hpp"
#include "armorobject.hpp"
#include "healthobject.hpp"
#include "poisonobject.hpp"
#include "plains.hpp"
#include "desert.hpp"
#include "proxylandscape.hpp"
#include "base.hpp"

void printBattleField(std::shared_ptr<BattleField> battleField) {
    std::string buf;
    
    for (int i = 0; i < battleField->getHeight(); ++i) {
        for (int  j = 0; j < battleField->getWidth(); ++j) {
            FieldCell& cell = battleField->getFieldCell(Position2D(j, i));
            if (cell.isEmpty()) {
                auto& object = *cell.getNeutralObject();
                auto& landscape = *cell.getLandscape();
                if (typeid (object) != typeid(NoObject)) {
                    std::cout << "? ";
                }
                else {
//                    if (typeid(landscape) == typeid(PlainsLandscape)) {
//                        std::cout << "- ";
//                    }
//                    else if (typeid(landscape) == typeid(OceansLandscape)) {
//                        std::cout << "~ ";
//                    }
//                    else {
//                        std::cout << ". ";
//                    }
//                    buf += landscape.draw();
                    std::cout << landscape.draw() <<" ";
                    
                }
//                buf += " ";
            }
            else {
                std::cout <<cell.getUnit()->getUnitName()[0]<<" ";
            }
        }
        std::cout << '\n';
    }
}


void test1(){
    std::shared_ptr<BattleField> battleField(new BattleField(10, 10));
    std::shared_ptr<Mediator> mediator(new Mediator(battleField));
    
    UnitCreator unitCreator;
    auto archer = unitCreator.createArcher(Position2D(0,0), mediator);
    auto dragon = unitCreator.createDragon(Position2D(6,7), mediator);
    auto swordman = unitCreator.createSwordMan(Position2D(5,4), mediator);
    auto vampire = unitCreator.createVampire(Position2D(9,2), mediator);
    auto ballistic = unitCreator.createBallistic(Position2D(4,8), mediator);


    battleField->addUnit(archer);
    battleField->addUnit(dragon);
    battleField->addUnit(swordman);
    battleField->addUnit(vampire);
    battleField->addUnit(ballistic);


    battleField->getFieldCell(Position2D(5,4)).getUnit()->moveRight();

    std::cout<< "BattleField created: " <<battleField->getWidth() <<" "<<battleField->getHeight()<<"\n";
    
    battleField->getFieldCellInfo(Position2D(5,4));
    battleField->getFieldCellInfo(Position2D(6,4));
    battleField->getFieldCellInfo(Position2D(6,7));
    printBattleField(battleField);

    std::cout<<"deleting unit from battleField\n";
    battleField->deleteUnit(archer);
//    battleField->deleteUnitCord(Position2D(6,7));
    
    battleField->getFieldCellInfo(Position2D(2,2));
    battleField->getFieldCellInfo(Position2D(6,7));
    printBattleField(battleField);
}
void test2(){
    std::shared_ptr<BattleField> battleField(new BattleField(10, 10));
       std::shared_ptr<Mediator> mediator(new Mediator(battleField));
       
       UnitCreator unitCreator;
       auto archer = unitCreator.createArcher(Position2D(2,2), mediator);
       auto dragon = unitCreator.createDragon(Position2D(6,7), mediator);
       auto swordman = unitCreator.createSwordMan(Position2D(5,4), mediator);
       auto vampire = unitCreator.createVampire(Position2D(9,2), mediator);
       auto ballistic = unitCreator.createBallistic(Position2D(4,8), mediator);


       
       battleField->addUnit(archer);
       battleField->addUnit(dragon);
       battleField->addUnit(swordman);
       battleField->addUnit(vampire);
       battleField->addUnit(ballistic);
    
    printBattleField(battleField);
    auto it = std::unique_ptr<BattleFieldIterator>(new BattleFieldIterator(*battleField));
    for (it->first(); it->hasNext(); ++*it) {
        if (!(**it).isEmpty()) {
            (**it).getUnit()->getUnitInfo();
        }
    }
}
void test3(){
    std::shared_ptr<BattleField> battleField(new BattleField(10, 10));
       std::shared_ptr<Mediator> mediator(new Mediator(battleField));
       
       UnitCreator unitCreator;
       auto archer = unitCreator.createArcher(Position2D(2,2), mediator);
       auto dragon = unitCreator.createDragon(Position2D(6,7), mediator);
       auto swordman = unitCreator.createSwordMan(Position2D(5,4), mediator);
       auto vampire = unitCreator.createVampire(Position2D(9,2), mediator);
       auto ballistic = unitCreator.createBallistic(Position2D(4,8), mediator);


       
       battleField->addUnit(archer);
       battleField->addUnit(dragon);
       battleField->addUnit(swordman);
       battleField->addUnit(vampire);
       battleField->addUnit(ballistic);
    
        std::cout<<"BEFORE MOVEMENT\n";
       printBattleField(battleField);
    
       while (archer->moveRight()) {
               ballistic->moveTop();
               dragon->moveLeft();
       }
    std::cout<<"\nAFTER MOVEMENT\n";
      printBattleField(battleField);

}
void test4(){
    std::shared_ptr<BattleField> battleField(new BattleField(10, 10));
       std::shared_ptr<Mediator> mediator(new Mediator(battleField));
       
       UnitCreator unitCreator;
       auto archer = unitCreator.createArcher(Position2D(2,2), mediator);
       auto dragon = unitCreator.createDragon(Position2D(6,7), mediator);
       auto swordman = unitCreator.createSwordMan(Position2D(5,4), mediator);
       auto vampire = unitCreator.createVampire(Position2D(9,2), mediator);
       auto ballistic = unitCreator.createBallistic(Position2D(4,8), mediator);


       
       battleField->addUnit(archer);
       battleField->addUnit(dragon);
       battleField->addUnit(swordman);
       battleField->addUnit(vampire);
       battleField->addUnit(ballistic);
    
       std::shared_ptr<BattleField> newbattle = std::make_shared<BattleField>(*battleField);
       
       battleField->deleteUnit(archer);
    
       battleField->getFieldCellInfo(Position2D(2, 2));
       std::cout<<"-----------\n";
       newbattle->getFieldCellInfo(Position2D(2, 2));
    
}
void testNeutralAndLandscape() {

    std::shared_ptr<BattleField> battleField(new BattleField(15, 15));
    std::shared_ptr<Mediator> mediator(new Mediator(battleField));

    auto desert = std::make_shared<DesertLandscape>();
    auto proxy = std::make_shared<ProxyLandscape>(desert);
       
    for (int j = 0; j < battleField->getWidth(); ++j) {
        battleField->getFieldCell(Position2D(j, 3)).setLandscape(proxy);
    }
       

       
    UnitCreator unitCreator;

    auto dragon = unitCreator.createDragon(Position2D(2,2), mediator);
    battleField->addUnit(dragon);
    
    auto healthObject = std::make_shared<HealthObject>();
    battleField->getFieldCell(Position2D(2, 4)).setNeutralObject(healthObject);

    auto poison = std::make_shared<PoisonObject>();
    battleField->getFieldCell(Position2D(4, 4)).setNeutralObject(poison);
    
    printBattleField(battleField);
    dragon->getUnitInfo();
    dragon->moveBottom();
    printBattleField(battleField);
    dragon->getUnitInfo();
    
//    dragon->moveBottom();
//    printBattleField(battleField);
//    dragon->getUnitInfo();
//    dragon->moveBottom();
//    printBattleField(battleField);
//    dragon->getUnitInfo();
    
//    dragon->moveBottom();
//    dragon->moveBottom();
//    printBattleField(battleField);
//    dragon->getUnitInfo();
//    dragon->moveRight();
//    dragon->moveRight();
//    printBattleField(battleField);
//    dragon->getUnitInfo();

}
void testBase(){
    std::shared_ptr<BattleField> battleField(new BattleField(20, 20));
    std::shared_ptr<Mediator> mediator(new Mediator(battleField));
        
    std::shared_ptr<Base> base(new Base(Position2D(0, battleField->getHeight()/2),mediator));
    battleField->addUnit(base);
    
    std::cout<< "Base added: \n";
    base->baseInfo();

    auto shortUnit = base->createShortRangeUnit(4, 1);
    auto longUnit = base->createLongRangeUnit(2, -2);
    auto dynamicUnit = base->createDynamicRangeUnit(5, 4);

    printBattleField(battleField);
    base->baseInfo();
//
    battleField->deleteUnit(shortUnit);
    
    shortUnit->notifyObservers();
    
    printBattleField(battleField);
    base->baseInfo();
    
}



int main() {
//    test1();
//    test2();
//    test3();
//    test4();
//    testNeutralAndLandscape();
    testBase();
    return 0;
}
