#include "Command.h"
#include "Units.h"
#include "GameUnits.h"
#include "Map.h"
#include "GameBlock.h"
#include "Base.h"
#include <iostream>

void HelpCommand::execute(){
    std::cout<<"wasd - for move, h - help, f - attack u - choosing fighter b - base control p - stop"<<std::endl;
}

void MoveCommand::execute(){
    (*death) = unitCont->moveUnit(x, y, index, *map);
}

void AttackCommand::execute(){
    unitCont->attack(index, *map, *enemies);
}




void CreateUnitInBaseCommand::execute(){
    baseCont->createUnit();
}


void BaseStatCommand::execute(){
    baseCont->showStat();
}


void SelectUnitInBaseCommand::execute(){
    while(1){
        newUnit = baseCont->getUnit();
        if(newUnit == nullptr){
            continue;
        }
        else{
            unitCont->addUnit(newUnit, baseCont->x, baseCont->y, *map);
            break;
        }
    }
}


void SwitchUnitCommand::execute(){
    (*index) = unitCont->changeActiveUnit();
}


BaseCommand::~BaseCommand(){
    delete baseCont;
}

UnitCommand::~UnitCommand(){
    delete unitCont;
}

SwitchUnitCommand::~SwitchUnitCommand(){
    delete unitCont;
    delete index;
}

MoveCommand::~MoveCommand(){
    delete map;
    delete death;
}

AttackCommand::~AttackCommand(){
    delete map;
    delete enemies;
}

SelectUnitInBaseCommand::~SelectUnitInBaseCommand(){
    delete unitCont;
    delete newUnit;
    delete map;
}

CreateBaseCommand::~CreateBaseCommand(){
    delete map;
}


//incorrect
void CreateBaseCommand::execute(){
   int x, y;
        do{
            std::cout<<"Enter coord for base: ";
            std::cin>>x>>y;

        } while(!(x > 0 && y > 0 && y <= map->getHeight() && x <= map->getWidth() && map->getBlock(y-1, x-1)->isEmpty()));
        x--;
        y--;
        baseCont = new Base(x, y);
        this->map->getBlock(y, x)->baseOnBlock = baseCont;
        baseCont->createUnit('L');
}

