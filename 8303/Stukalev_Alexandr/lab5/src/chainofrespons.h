#ifndef CHAINOFRESPONS_H
#define CHAINOFRESPONS_H
#include "field.h"
#include "command.h"

class ChainOfRespons
{
    ChainOfRespons* nextComm;
protected:
    Field* field;
    Mediator* mediator;
    Snapshot* snapshot;
    ChainOfRespons(Field* field) : nextComm(nullptr), field(field){}
    ChainOfRespons(Field* field, Snapshot* snapshot) : nextComm(nullptr), field(field), snapshot(snapshot){}
public:
    ChainOfRespons() : nextComm(nullptr) {}
    void setNext(ChainOfRespons* nextComm)
    {
        this->nextComm = nextComm;
    }
    void addToChain(ChainOfRespons* nextComm)
    {
        if (this->nextComm != nullptr)
            this->nextComm->addToChain(nextComm);
        else
            this->nextComm = nextComm;
    }
    virtual void chain(string command)
    {
        this->nextComm->chain(command);
    }
    virtual ~ChainOfRespons(){}
};

class ElemUnitCreat: public ChainOfRespons
{
public:
    ElemUnitCreat(Field* field) : ChainOfRespons(field){};
    void chain(string command) override
    {
        if(command == "create")
        {
            Command* curr_com = new CreateUnitComm(this->field);
            curr_com->execute();
            this->field->print_field();

        }
        else
            ChainOfRespons::chain(command);
    }
};

class ElemUnitMove: public ChainOfRespons
{
public:
    ElemUnitMove(Field* field) : ChainOfRespons(field){}
    void chain(string command) override
    {
        if(command == "move")
        {
            Command* curr_com = new MoveUnitComm(this->field);
            curr_com->execute();
            this->field->print_field();
        }
        else
            ChainOfRespons::chain(command);
    }
};

class ElemUnitAttack: public ChainOfRespons
{
public:
    ElemUnitAttack(Field* field) : ChainOfRespons(field){}
    void chain(string command) override
    {
        if(command == "attack")
        {
            Mediator* mediator = new Mediator(this->field);
            Command* curr_com = new AttackComm(this->field,mediator);
            curr_com->execute();
            this->field->print_field();
        }
        else
            ChainOfRespons::chain(command);
        }
};


class ElemBaseStatus: public ChainOfRespons
{
public:
    ElemBaseStatus(Field* field) : ChainOfRespons(field){}
    void chain(string command) override
    {
        if(command == "status")
        {
            Command* curr_com = new BaseStatusComm(this->field);
            curr_com->execute();
        }
        else
            ChainOfRespons::chain(command);
        }
};

class ElemLogging: public ChainOfRespons
{
public:
    ElemLogging(Field* field) : ChainOfRespons(field){}
    void chain(string command) override
    {
        if(command == "log")
        {
            Command* curr_com = new LoggingComm(this->field);
            curr_com->execute();
        }
        else
            ChainOfRespons::chain(command);
        }
};

class ElemWrongComm: public ChainOfRespons
{

public:
    void chain(string command){
        cout << "\nWrong command!\n";
   }
};

class ElemSaveComm: public ChainOfRespons
{
public:
    ElemSaveComm(Field* field): ChainOfRespons(field){}
    void chain(string command) override
    {
        if(command == "save")
        {
            Snapshot* snap = new Snapshot(this->field);
            Command* curr_com = new SaveComm(this->field, snap);
            delete snap;
            curr_com->execute();
        }
        else
            ChainOfRespons::chain(command);
        }
};


class ElemLoadComm: public ChainOfRespons
{
public:
    ElemLoadComm(Field* field): ChainOfRespons(field){}
    void chain(string command) override
    {
        if(command == "load")
        {
            Snapshot* snap = new Snapshot(this->field);
            Command* curr_com = new LoadComm(this->field, snap);
            delete snap;
            curr_com->execute();
            this->field->print_field();
        }
        else
            ChainOfRespons::chain(command);
        }
};

#endif // CHAINOFRESPONS_H
