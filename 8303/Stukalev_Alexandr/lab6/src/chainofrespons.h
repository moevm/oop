#ifndef CHAINOFRESPONS_H
#define CHAINOFRESPONS_H
#include "field.h"
#include "command.h"
#include "myexeptions.h"

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
    void setNext(ChainOfRespons* nextComm, char base)
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
    virtual void chain(string command, char base)
    {
        this->nextComm->chain(command, base);
    }
    virtual ~ChainOfRespons(){}
};

class ElemUnitCreat: public ChainOfRespons
{
public:
    ElemUnitCreat(Field* field) : ChainOfRespons(field){}
    void chain(string command, char base) override
    {
        if(command == "create")
        {
            try
            {
                Command* curr_com = new CreateUnitComm(this->field, base);
                curr_com->execute();
                this->field->print_field();
            }
            catch(LogicalExceptions e)
            {
                std::cout << e.what() << "\n";
                ElemUnitCreat(this->field);
            }
            catch(TypeExceptions e)
            {
                std::cout << e.what() << "\n";
                ElemUnitCreat(this->field);
            }
            catch(OutOfRangeExceptions e)
            {
                std::cout << e.what() << "\n";
                ElemUnitCreat(this->field);
            }
        }
        else
            ChainOfRespons::chain(command, base);
    }
};

class ElemUnitMove: public ChainOfRespons
{
public:
    ElemUnitMove(Field* field) : ChainOfRespons(field){}
    void chain(string command, char base) override
    {
        if(command == "move")
        {
            try
            {
                Command* curr_com = new MoveUnitComm(this->field, base);
                curr_com->execute();
                this->field->print_field();
            }
            catch(LogicalExceptions e)
            {
                std::cout << e.what() << "\n";
                ElemUnitMove(this->field);
            }
            catch(TypeExceptions e)
            {
                std::cout << e.what() << "\n";
                ElemUnitMove(this->field);
            }
            catch(OutOfRangeExceptions e)
            {
                std::cout << e.what() << "\n";
                ElemUnitMove(this->field);
            }

        }
        else
            ChainOfRespons::chain(command, base);
    }
};

class ElemUnitAttack: public ChainOfRespons
{
public:
    ElemUnitAttack(Field* field) : ChainOfRespons(field){}
    void chain(string command, char base) override
    {
        if(command == "attack")
        {
            try
            {
                Mediator* mediator = new Mediator(this->field);
                Command* curr_com = new AttackComm(this->field,mediator, base);
                curr_com->execute();
                this->field->print_field();
            }
            catch(LogicalExceptions e)
            {
                std::cout << e.what() << "\n";
                ElemUnitAttack(this->field);
            }
            catch(TypeExceptions e)
            {
                std::cout << e.what() << "\n";
                ElemUnitAttack(this->field);
            }
            catch(OutOfRangeExceptions e)
            {
                std::cout << e.what() << "\n";
                ElemUnitAttack(this->field);
            }

        }
        else
            ChainOfRespons::chain(command, base);
    }
};


class ElemBaseStatus: public ChainOfRespons
{
public:
    ElemBaseStatus(Field* field) : ChainOfRespons(field){}
    void chain(string command, char base) override
    {
        if(command == "status")
        {
            try
            {
                Command* curr_com = new BaseStatusComm(this->field, base);
                curr_com->execute();
            }
            catch(LogicalExceptions e)
            {
                std::cout << e.what() << "\n";
                ElemBaseStatus(this->field);
            }
            catch(TypeExceptions e)
            {
                std::cout << e.what() << "\n";
                ElemBaseStatus(this->field);
            }
            catch(OutOfRangeExceptions e)
            {
                std::cout << e.what() << "\n";
                ElemBaseStatus(this->field);
            }
        }
        else
            ChainOfRespons::chain(command, base);
    }
};

class ElemLogging: public ChainOfRespons
{
public:
    ElemLogging(Field* field) : ChainOfRespons(field){}
    void chain(string command, char base) override
    {
        if(command == "log")
        {           
            try
            {
                Command* curr_com = new LoggingComm(this->field);
                curr_com->execute();
            }
            catch(LogicalExceptions e)
            {
                std::cout << e.what() << "\n";
                ElemLogging(this->field);
            }
            catch(TypeExceptions e)
            {
                std::cout << e.what() << "\n";
                ElemLogging(this->field);
            }
            catch(OutOfRangeExceptions e)
            {
                std::cout << e.what() << "\n";
                ElemLogging(this->field);
            }
        }
        else
            ChainOfRespons::chain(command, base);
    }
};

class ElemWrongComm: public ChainOfRespons
{

public:
    void chain(string command, char base) override
    {
        cout << "\nWrong command!\n";
    }
};

class ElemSaveComm: public ChainOfRespons
{
public:
    ElemSaveComm(Field* field): ChainOfRespons(field){}
    void chain(string command, char base) override
    {
        if(command == "save")
        {
            try
            {
                Snapshot* snap = new Snapshot(this->field);
                Command* curr_com = new SaveComm(this->field, snap);
                delete snap;
                curr_com->execute();
            }
            catch(LogicalExceptions e)
            {
                std::cout << e.what() << "\n";
                ElemSaveComm(this->field);
            }
            catch(TypeExceptions e)
            {
                std::cout << e.what() << "\n";
                ElemSaveComm(this->field);
            }
            catch(OutOfRangeExceptions e)
            {
                std::cout << e.what() << "\n";
                ElemSaveComm(this->field);
            }
        }
        else
            ChainOfRespons::chain(command, base);
    }
};


class ElemLoadComm: public ChainOfRespons
{
public:
    ElemLoadComm(Field* field): ChainOfRespons(field){}
    void chain(string command, char base) override
    {
        if(command == "load")
        {
            try
            {
                Snapshot* snap = new Snapshot(this->field);
                Command* curr_com = new LoadComm(this->field, snap);
                delete snap;
                curr_com->execute();
                this->field->print_field();
            }
            catch(LogicalExceptions e)
            {
                std::cout << e.what() << "\n";
                ElemLoadComm(this->field);
            }
            catch(TypeExceptions e)
            {
                std::cout << e.what() << "\n";
                ElemLoadComm(this->field);
            }
            catch(OutOfRangeExceptions e)
            {
                std::cout << e.what() << "\n";
                ElemLoadComm(this->field);
            }
        }
        else
            ChainOfRespons::chain(command, base);
    }
};


class ElemNextComm: public ChainOfRespons
{
public:
    ElemNextComm(Field* field): ChainOfRespons(field){}
    void chain(string command, char base) override
    {
        if(command == "next")
        {
            try
            {
                Command* curr_com = new NextComm(this->field, base);
                curr_com->execute();
                this->field->print_field();
            }
            catch(LogicalExceptions e)
            {
                std::cout << e.what() << "\n";
                ElemNextComm(this->field);
            }
            catch(TypeExceptions e)
            {
                std::cout << e.what() << "\n";
                ElemNextComm(this->field);
            }
            catch(OutOfRangeExceptions e)
            {
                std::cout << e.what() << "\n";
                ElemNextComm(this->field);
            }
        }
        else
            ChainOfRespons::chain(command, base);
        }

};

#endif // CHAINOFRESPONS_H
