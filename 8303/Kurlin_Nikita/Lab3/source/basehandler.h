#ifndef BASEHANDLER_H
#define BASEHANDLER_H

#include <string>
#include <algorithm>
#include "base.h"
#include "gamefield.h"
#include "command.h"

using namespace std;

class BaseHandler{

    BaseHandler* next;

protected:
    GameField* field;
    Mediator* mediator;
    BaseHandler(GameField* field) : next(nullptr), field(field){}
    BaseHandler(GameField* field, Mediator* mediator) : next(nullptr), field(field), mediator(mediator){}

public:
    BaseHandler() : next(nullptr) {}

    void setNext(BaseHandler* next){
        this->next = next;
    }

    void add(BaseHandler* next){
        if (this->next)
            this->next->add(next);
        else
            this->next = next;
    }

    virtual void handle(string command){
        this->next->handle(command);
    }

    virtual ~BaseHandler(){}
};

class CreateBaseHandler : public BaseHandler{

public:
    CreateBaseHandler(GameField* field) : BaseHandler(field) {}
    void handle(string command) override{
        transform(command.begin(), command.end(), command.begin(), tolower);
        if (command == "create base"){
            Command* createBase = new CreateBaseCommand(field);
            createBase->execute();
        }
        else{
            BaseHandler::handle(command);
        }
   }
};

class CreateUnitHandler : public BaseHandler{

public:
    CreateUnitHandler(GameField* field, Mediator* mediator) : BaseHandler(field, mediator) {}
    void handle(string command) override{
        transform(command.begin(), command.end(), command.begin(), tolower);
        if (command == "create unit"){
            Command* createUnit = new CreateUnitCommand(field, mediator);
            createUnit->execute();
        }
        else{
            BaseHandler::handle(command);
        }
   }
};

class WrongCommandHandler : public BaseHandler{

public:
    void handle(string command) override{
        cout << "\nThe command doesn't exist!\n";
   }
};

class MoveUnitHandler : public BaseHandler{

public:
    MoveUnitHandler(GameField* field) : BaseHandler(field) {}
    void handle(string command) override{
        transform(command.begin(), command.end(), command.begin(), tolower);
        if (command == "move unit"){
            Command* moveUnit = new MoveUnitCommand(field);
            moveUnit->execute();
        }
        else{
            BaseHandler::handle(command);
        }
   }
};

class BaseStatusHandler : public BaseHandler{

public:
    BaseStatusHandler(GameField* field) : BaseHandler(field) {}
    void handle(string command) override{
        transform(command.begin(), command.end(), command.begin(), tolower);
        if (command == "base status"){
            Command* baseStatus = new BaseStatusCommand(field);
            baseStatus->execute();
        }
        else{
            BaseHandler::handle(command);
        }
   }
};

class AttackHandler : public BaseHandler{

public:
    AttackHandler(GameField* field, Mediator* mediator) : BaseHandler(field, mediator) {}
    void handle(string command) override{
        transform(command.begin(), command.end(), command.begin(), tolower);
        if (command == "attack"){
            Command* Attack = new AttackCommand(field, mediator);
            Attack->execute();
        }
        else{
            BaseHandler::handle(command);
        }
   }
};

#endif // BASEHANDLER_H
