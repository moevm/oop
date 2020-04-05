//
// Created by Artem Butko on 04/04/2020.
//

#include "CoR.h"

CoR::CoR(GameField *Field) : Field(Field)
{
    next = nullptr;
}

void CoR::setNext(CoR* nextChain)
{
    next = nextChain;
}

void CoR::addNext(CoR* nextChain)
{
    if(next) next->addNext(nextChain);
    else next = nextChain;
}

void CoR::chain(std::string commandID)
{
    next->chain(commandID);
}

CoR::CoR()
{
    next = nullptr;
}

void CreateBaseCOR::chain(std::string commandID)
{
    if (commandID == "CreateBase"){
        Command* command = new createBaseCommand(Field);
        command->gameCommand();
    }
    else CoR::chain(commandID);
}

void InfoBaseCOR::chain(std::string commandID)
{
    if (commandID == "InfoBase"){
        Command* command = new infoBaseCommand(Field);
        command->gameCommand();
    }
    else CoR::chain(commandID);
}

void CreateUnitCOR::chain(std::string commandID)
{
    if (commandID == "CreateUnit"){
        Command* command = new createUnitCommand(Field);
        command->gameCommand();
    }
    else CoR::chain(commandID);
}

void GetUnitCOR::chain(std::string commandID)
{
    if (commandID == "GetUnit"){
        Command* command = new getUnitCommand(Field);
        command->gameCommand();
    }
    else CoR::chain(commandID);
}

void MoveUnitCOR::chain(std::string commandID)
{
    if (commandID == "MoveUnit"){
        Command* command = new moveUnitCommand(Field);
        command->gameCommand();
    }
    else CoR::chain(commandID);
}

void UnknownCOR::chain(std::string commandID)
{
    Command* command = new noneCommand;
    command->gameCommand();
}
