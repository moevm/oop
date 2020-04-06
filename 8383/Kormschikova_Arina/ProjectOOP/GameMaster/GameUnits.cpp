
#include <stdio.h>
#include <iostream>
#include "GameUnits.h"
#include "Units.h"
#include "Map.h"
#include "GameBlock.h"


GameUnits::GameUnits() {
    size = 0;
    type = 0;
}

void GameUnits::addUnit(Unit *unit, int x, int y, GameMap &gameMap){
    this->size++;
    units.push_back(unit);
    units[size-1]->x = x;
    units[size-1]->y = y;
    gameMap.map[y][x].setUnit(unit);
}


Unit* GameUnits::getUnit(int x, int y) {
    for (int i = 0; i < size; i++) {
        if (units[i]->x == x && units[i]->y == y) return units[i];
    }
    
    return nullptr;
}

//
bool GameUnits::moveUnit(int x, int y, int index, GameMap &gameMap) {
    units[index]->move(x, y, gameMap);
    if(units[index]->hitPoint < 1){
        return 1;
    }
    return 0;
}



void GameUnits::update(){
    for(auto iter = units.begin(); iter < units.end(); iter++){
        if( (*iter)->hitPoint < 0){
             size--;
             units.erase(iter);
         }
     }
}

int GameUnits::changeActiveUnit(){
    int index;
    std::cout<<"Choose your fighter"<<std::endl;
    for(int i = 0; i < this->units.size(); i++){
        std::cout<<i+1<<" "<<std::endl;
        this->units[i]->showStat();
    }
    while(1){
        std::cin>>index;
        if(index < 1 || index > this->units.size()){
            std::cout<<"Wrong!"<<std::endl;
        }
        else{
            index--;
            return index;
        }
    }
}

void GameUnits::attack(int index, GameMap &gameMap, EnemiesUnits& enemies){
    
    int topBorder = (units[index]->y - units[index]->weapon->radius)< 0 ? 0 : (units[index]->y - units[index]->weapon->radius);
    int leftBorder = (units[index]->x - units[index]->weapon->radius)< 0 ? 0 : (units[index]->x - units[index]->weapon->radius);
    int rightBorder = (units[index]->x + units[index]->weapon->radius)>gameMap.width ? (gameMap.width-1):(units[index]->x + units[index]->weapon->radius);
    int bottomBorder = (units[index]->y + units[index]->weapon->radius)>gameMap.height ? (gameMap.height - 1): (units[index]->y + units[index]->weapon->radius);
    GameBlock* currentBlock;
    std::vector <Unit*> enemiesList;
    Unit* newEnemy;
    int k = 0;
    
    for(int i =  leftBorder; i <= rightBorder; i++){
        for(int j = topBorder; j <= bottomBorder; j++){
            if(units[index]->checkForAttack(i, j)){
                currentBlock = gameMap.getBlock(j, i);
                if(currentBlock->unitOnBlock!=nullptr){
                    newEnemy = enemies.getUnit(i, j);
                    if(newEnemy != nullptr){
                        enemiesList.push_back(newEnemy);
                        k++;
                        std::cout<<k<<") You can attack "<<newEnemy->type<<" standing on x = "<<i+1<<" y = "<<j+1<<std::endl;
                    }
                }
            }
        }
    }
    if(enemiesList.size() == 0){
        std::cout<<"There are no enemies in your area!"<<std::endl;
        return;
    }
    int input = -1;
    std::cout<<"Which one will be attacked? 0 - Сancel "<<std::endl;
    while(1){
        std::cin>>input;
        if(input < 0 || input > enemiesList.size()){
            std::cout<<"Wrong command"<<std::endl;
        }
        else{
            break;
        }
    }
    if(input == 0){
        return;
    }
    units[index]->attack(enemiesList[input-1]);
    for(int i = 0; i < enemiesList.size(); i++){
        if(gameMap.getBlock(enemiesList[i]->y, enemiesList[i]->x)->unitOnBlock->hitPoint <= 0){
            gameMap.getBlock(enemiesList[i]->y, enemiesList[i]->x)->unitOnBlock = nullptr;
        }
    }
    enemies.update();
}

