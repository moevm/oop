#include <iostream>
#include "Command.h"
#include "Units.h"
#include "GameUnits.h"
#include "Map.h"
#include "GameBlock.h"
#include "Base.h"
#include "Handler.h"



Handler* AbstractHandler::setNext(Handler* handler){
    this->nextHandler = handler;
    return handler;
}

Command* AbstractHandler::handle(char request, GameMap *map, FriendsUnits* units, EnemiesUnits* enemies, Base *base, int* index, bool* death){
    if(this->nextHandler){
        return this->nextHandler->handle(request, map, units, enemies, base, index, death);
    }
    return {};
}

Command* AttackHandler::handle(char request, GameMap *map, FriendsUnits* units, EnemiesUnits* enemies, Base *base, int* index, bool* death){
    if(request == 'f'){
        return new AttackCommand(map, enemies, units, *index);
    }
    return AbstractHandler::handle(request, map, units, enemies, base, index, death);
}

Command* MoveHandler::handle(char request, GameMap *map, FriendsUnits* units, EnemiesUnits* enemies, Base *base, int* index, bool* death){
    switch (request) {
        case 'w':
            return new MoveCommand(0, -1, *index, map, units, death);
        case 's':
            return new MoveCommand(0, 1, *index, map, units, death);
        case 'd':
            return new MoveCommand(1, 0, *index, map, units, death);
        case 'a':
            return new MoveCommand(-1, 0, *index, map, units, death);
        default:
            return AbstractHandler::handle(request, map, units, enemies, base, index, death);
    }
}

Command* ChangeUnitHandler::handle(char request, GameMap *map, FriendsUnits* units, EnemiesUnits* enemies, Base *base, int* index, bool* death){
    if(request == 'u'){
        return new SwitchUnitCommand(units, index);
    }
    return AbstractHandler::handle(request, map, units, enemies, base, index, death);
}

Command* BaseControlHandler::handle(char request, GameMap *map, FriendsUnits* units, EnemiesUnits* enemies, Base *base, int* index, bool* death){
    if(request == 'b'){
        Command* command;
        if(base == nullptr){
            command = new CreateBaseCommand(base, map);
            command->execute();
        }
        base->baseUpdate();
        char input;
        do{
            std::cout<<"Enter command for base 'c' - Create unit, 's' - select unit: "<<std::endl;
            std::cin>>input;
            std::cout<<std::endl;
            switch (input) {
                case 'c':
                    command = new CreateUnitInBaseCommand(base);
                    command->execute();
                    break;
                case 's':
                    return new SelectUnitInBaseCommand(units, base, map);
                default:
                    break;
            }
            
        }while(1);
    }
    return AbstractHandler::handle(request, map, units, enemies, base, index, death);
}

Command* HelpHandler::handle(char request, GameMap *map, FriendsUnits* units, EnemiesUnits* enemies, Base *base, int* index, bool* death){
    if(request == 'h'){
        return new HelpCommand;
    }
    return AbstractHandler::handle(request, map, units, enemies, base, index, death);
}
