//
// Created by anton on 03.04.2020.
//

#ifndef OOP_1_HANDLER_H
#define OOP_1_HANDLER_H

#include <string>
#include "Command.h"
#include "Adapter.h"

class Command;

class BaseHandler
{
    BaseHandler* next;
protected:
    Field* field;
public:
    explicit BaseHandler(Field*);

    void setNext(BaseHandler* next);

    virtual void handle(std::string& command) {
        if(next)
            next->handle(command);
        else
        {
            std::cout << "incorrect command!" << std::endl;
            std::cout << "use help" << std::endl;
        }
    }
};

class SetBaseHandler: public BaseHandler {
    int numberBase;
public:
    explicit SetBaseHandler(Field*);

    void handle(std::string& command) override;
};

class SetUnitHandler: public BaseHandler {
public:
    explicit SetUnitHandler(Field*);

    void handle(std::string& command) override;
};


class MoveUnitUpHandler: public BaseHandler {
public:
    explicit MoveUnitUpHandler(Field*);

    void handle(std::string& command) override;
};

class MoveUnitDownHandler: public BaseHandler {
public:
    explicit MoveUnitDownHandler(Field*);

    void handle(std::string& command) override;
};

class MoveUnitRightHandler: public BaseHandler {
public:
    explicit MoveUnitRightHandler(Field*);

    void handle(std::string& command) override;
};

class MoveUnitLeftHandler: public BaseHandler {
public:
    explicit MoveUnitLeftHandler(Field*);

    void handle(std::string& command) override;
};

class AttackUnitHandler: public BaseHandler {
public:
    explicit AttackUnitHandler(Field*);

    void handle(std::string& command) override;
};


class ShowStatusHandler: public BaseHandler {
public:
    explicit ShowStatusHandler(Field*);

    void handle(std::string& command) override;
};

class HelpHandler: public BaseHandler {
public:
    explicit HelpHandler(Field*);
    void handle(std::string& command) override;
};

class SwitchLogHandler: public BaseHandler{
    Adapter* adapter;
public:
    explicit SwitchLogHandler(Adapter* );

    void handle(std::string& command) override ;
};

class TurnOnOffLog: public BaseHandler{
    Adapter* adapter;
public:
    explicit TurnOnOffLog(Adapter*);

    void handle(std::string& command) override ;
};

#endif //OOP_1_HANDLER_H
