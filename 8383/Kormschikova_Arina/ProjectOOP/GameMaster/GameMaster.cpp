
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "GameMaster.h"
#include "Map.h"
#include "Base.h" 
#include "Units.h"
#include "GameVisualization.h"
#include "GameBlock.h"
#include "NeutralObject.h"
#include "GameUnits.h"
#include "Invoker.h"
#include "Command.h"
#include "Handler.h"

GameMaster::GameMaster(){
    srand(time(0));
    base = nullptr;
    map = nullptr;
    invoker = nullptr;
    units = new FriendsUnits;
    enemies = new EnemiesUnits;
    gameCycle();
       
}


void GameMaster::setMap(){
    int width, height;
    do{
        width = 9;
        height = 9;
//        std::cout<<"Enter map size: ";
//        std::cin>>width>>height;
        

    } while( !(width > 0 && height > 0));
    map = new GameMap(height, width);

//creating default map
   for(int i = 4; i < 7; i++){
       for(int j = 5; j <8; j++){
           map->getBlock(j, i)->landscape = new Water;
       }
   }
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5-i; j++){
            map->getBlock(i, j)->landscape = new Forest;
        }
    }
    
    map->getBlock(0,5)->objectOnBlock = new MrWitcher;
    map->getBlock(6, 2)->objectOnBlock = new Bonfire;
    map->getBlock(7, 7)->objectOnBlock = new Grave;
    map->getBlock(2, 7)->objectOnBlock = new Bird;
}


void GameMaster::setBase(){
    int x, y;
    do{
        std::cout<<"Enter coord for base: ";
        std::cin>>x>>y;

    } while(!(x > 0 && y > 0 && y <= map->getHeight() && x <= map->getWidth() && map->getBlock(y-1, x-1)->isEmpty()));
    x--;
    y--;
    base = new Base(x, y);
    
    this->map->getBlock(y, x)->baseOnBlock = new Base(x, y);
    base->createUnit('L');
    //update(*map);
    base->showStat();
}


void GameMaster::setEnemies(){
    Unit* newEnemy = new Paladin;
    enemies->addUnit(newEnemy, 4, 2, *map);
    newEnemy = new LanceKnight;
    enemies->addUnit(newEnemy, 0, 6, *map);
    newEnemy = new Slayer;
    enemies->addUnit(newEnemy, 2, 7, *map);
    newEnemy = new Witch;
    enemies->addUnit(newEnemy, 1, 2, *map);
}



//
//void GameMaster::gameCycle(){
//    char input;
//    int index = 0;
//    setMap();
//    setEnemies();
//
//    update(*map);
////    setBase();
//    invoker = new Invoker(map, units, enemies, base, &index);
//    invoker->invokerCycle('b');
//    do{
//        update(*map);
//        std::cout << "Enter command: ";
//        std::cin >> input;
//        std::cout<<std::endl;
//        invoker->invokerCycle(input);
//    }while (input != 'p');
//}


void GameMaster::baseControl(){
    if(this->base == nullptr){
        setBase();
        update(*map);
    }
    base->baseUpdate();
    char input;
    do{
        std::cout<<"Enter command for base 'c' - Create unit, 's' - select unit, t - show stat: "<<std::endl;
        std::cin>>input;
        std::cout<<std::endl;
        switch (input) {
            case 'c':
                command = new CreateUnitInBaseCommand(base);
                command->execute();
                break;
            case 's':
                command = new SelectUnitInBaseCommand(units, base, map);
                command->execute();
                input = 'w';
                break;
            case 't':
                command = new BaseStatCommand(base);
                command->execute();
                break;
            default:
                break;
        }

    }while(input != 'w');
}



void GameMaster::gameCycle() {
    char input;
    setMap();
    setEnemies();
    update(*map);
    baseControl();
    int index = 0;
    bool deathCheck = false;
    do {
        update(*map);
        std::cout << "Enter command: ";
        std::cin >> input;
        std::cout<<std::endl;
        switch (input) {
            case 'w':
                command = new MoveCommand(0, -1, index, map, units, &deathCheck);
                command->execute();
                break;
            case 's':
                command = new MoveCommand(0, 1, index, map, units, &deathCheck);
                command->execute();
                break;
            case 'd':
                command = new MoveCommand(1, 0, index, map, units, &deathCheck);
                command->execute();
                break;
            case 'a':
                command = new MoveCommand(-1, 0, index, map, units, &deathCheck);
                command->execute();
                break;
            case 'f':
                command = new AttackCommand(map, enemies, units, index);
                command->execute();

                break;
            case 'b':
                baseControl();
                index++;
                break;
            case 'u':
                command = new SwitchUnitCommand(units, &index);
                command->execute();

                break;
            case 'h':
                command = new HelpCommand();
                command->execute();
                break;
            default:
                break;

        }
        if(deathCheck){
            map->getBlock(units->units[index]->y, units->units[index]->x )->unitOnBlock = nullptr;
            units->units.pop_back();
            units->size--;
            update(*map);
            baseControl();
        }
    } while (input != 'p');
}

//
//
