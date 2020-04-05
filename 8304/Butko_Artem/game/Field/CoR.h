//
// Created by Artem Butko on 04/04/2020.
//

#ifndef NEW_LR1_COR_H
#define NEW_LR1_COR_H

#include "GameField.h"
#include "Object/Base.h"
#include "Commands/Command.h"
#include "Commands/BaseCommands/createBaseCommand.h"
#include "Commands/BaseCommands/infoBaseCommand.h"
#include "Commands/UnitCommands/createUnitCommand.h"
#include "Commands/UnitCommands/getUnitCommand.h"
#include "Commands/UnitCommands/moveUnitCommand.h"
#include "Commands/UnknownCommands/noneCommand.h"

class CoR
{
    CoR *next;
protected:
    CoR(GameField* Field);
    GameField* Field;
public:
    CoR();
    void setNext(CoR* nextChain);
    void addNext(CoR* nextChain);
    virtual void chain(std::string commandID);
};

class CreateBaseCOR : public CoR
{
public:
    CreateBaseCOR(GameField* Field) : CoR(Field) {};
    void chain(std::string commandID) override;
};

class InfoBaseCOR : public CoR
{
public:
    InfoBaseCOR(GameField* Field) : CoR(Field) {};
    void chain(std::string commandID) override;
};

class CreateUnitCOR : public CoR
{
public:
    CreateUnitCOR(GameField* Field) : CoR(Field) {};
    void chain(std::string commandID) override;
};

class GetUnitCOR : public CoR
{
public:
    GetUnitCOR(GameField* Field) : CoR(Field) {};
    void chain(std::string commandID) override;
};

class MoveUnitCOR : public CoR
{
public:
    MoveUnitCOR(GameField* Field) : CoR(Field) {};
    void chain(std::string commandID) override;
};

class UnknownCOR : public CoR
{
public:
    UnknownCOR(GameField* Field) : CoR(nullptr) {};
    void chain(std::string commandID) override;
};

#endif //NEW_LR1_COR_H
