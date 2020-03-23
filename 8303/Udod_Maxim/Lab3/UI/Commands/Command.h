//
// Created by shenk on 16.03.2020.
//

#ifndef UNTITLED13_COMMAND_H
#define UNTITLED13_COMMAND_H

#include <string>
#include <memory>
#include "../../GameField/GameField.h"
#include "../../GameInfo.h"

class Command {

public:

    virtual void execute(GameInfo &gameInfo, GameField &gameField){}

};

typedef std::unique_ptr<Command> CommandPtr;

class CommandHandler{

private:

    virtual CommandPtr handle(std::vector<std::string> &cmd)=0;

};


#endif //UNTITLED13_COMMAND_H
