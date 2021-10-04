#ifndef OOP1_HANDLER_H
#define OOP1_HANDLER_H

#include <string>
#include <iostream>
#include "Base.h"
#include "Field.h"
#include "Command.h"

class BaseHandler{
    BaseHandler* next;
protected:
    Field* field;


    BaseHandler(Field* field): field(field){
        next = nullptr;
    }
public:
    BaseHandler(){
        next = nullptr;
    }


    void setNext(BaseHandler *n){
        next = n;
        }
    void add(BaseHandler *n){
        if (next)
            next->add(n);
        else
            next = n;
    }

    virtual void handle(std::string commandStr)
    {
        next->handle(commandStr);
    }
};

class SetBaseHandler: public BaseHandler{
public:
    SetBaseHandler(Field* field): BaseHandler(field){

    }
    void handle (std::string commandStr) override {
        if (commandStr == "setBase"){
            BaseCommand* setBase = new SetBaseCommand(field);
            setBase->execute();
        }
        else{
            BaseHandler::handle(commandStr);
        }

    }
};

class SetUnitHandler: public BaseHandler{
    Mediator* mediator;
public:
    SetUnitHandler(Field* field, Mediator* mediator): BaseHandler(field), mediator(mediator){

    }
    void handle (std::string commandStr) override {
        if (commandStr == "setUnit"){
            BaseCommand* setUnit = new CreateUnitCommand(field, mediator);
            setUnit->execute();

        }
        else{
            BaseHandler::handle(commandStr);
        }

    }
};

class AttackUnitHandler: public BaseHandler{
    Mediator* mediator;
public:
    AttackUnitHandler(Field* field, Mediator* mediator): BaseHandler(field), mediator(mediator){

    }
    void handle (std::string commandStr) override {
        if (commandStr == "attackUnit"){
            BaseCommand* attackUnit = new AttackUnitCommand(field, mediator);
            attackUnit->execute();

        }
        else{
            BaseHandler::handle(commandStr);
        }

    }
};

class StatusBaseHandler: public BaseHandler{
public:
    StatusBaseHandler(Field* field): BaseHandler(field){

    }
    void handle (std::string commandStr) override {
        if (commandStr == "statusBase"){
            StatusBaseCommand* statusBase = new StatusBaseCommand(field);
            statusBase->execute();

        }
        else{
            BaseHandler::handle(commandStr);
        }

    }
};

class MoveUnitHandler: public BaseHandler{
public:
    MoveUnitHandler(Field* field): BaseHandler(field){

    }
    void handle (std::string commandStr) override {
        if (commandStr == "moveUnit"){
            MoveUnitCommand* moveUnit = new MoveUnitCommand(field);
            moveUnit->execute();

        }
        else{
            BaseHandler::handle(commandStr);
        }

    }
};

class NoCommandHandler: public BaseHandler{
public:

    void handle (std::string commandStr) override {
        std::cout << "Not this command!" << std::endl;
    }
};

#endif //OOP1_HANDLER_H
