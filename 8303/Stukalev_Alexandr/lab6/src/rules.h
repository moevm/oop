#ifndef RULES_H
#define RULES_H

#include "chainofrespons.h"
#include "myexeptions.h"

class State
{
public:
    virtual void handle(std::string command, ChainOfRespons* chain) = 0;
};

class AlienPlayerState: public State
{
public:
    void handle(std::string command, ChainOfRespons* chain) override
    {
        chain->chain(command, 'A');
    }
};

class HumanPlayerState: public State
{
public:
    void handle(std::string command, ChainOfRespons* chain) override
    {
        chain->chain(command, 'H');
    }
};

class Rule
{
protected:
    Field* field;
    State* alienplayerstate;
    State* humanplayerstate;
    State* currstate;
public:
    virtual Field* createField() = 0;
    virtual void handle(const std::string command, ChainOfRespons* chainofrespons, int* counturns) = 0;
    virtual int defeat(int countofturns) = 0;
    Rule()
    {
        alienplayerstate = new AlienPlayerState();
        humanplayerstate = new HumanPlayerState();
        currstate = humanplayerstate;
    }

    void changeState()
    {
        if(currstate = humanplayerstate)
            currstate = alienplayerstate;
        else if(currstate = alienplayerstate)
            currstate = humanplayerstate;
    }
};

class ShortGameRule: public Rule
{
public:
    Field* createField() override
    {
        this->field = new Field(10, 10);
        while(!field->checkAleinBase() || !field->checkHumanBase())
        {
            try
            {
                Command* createbases = new CreateBaseComm(this->field);
                createbases->execute();
            }
            catch(LogicalExceptions e)
            {
                std::cout << e.what() << "\n";
                this->field = createField();
            }
            catch(TypeExceptions e)
            {
                std::cout << e.what() << "\n";
                this->field = createField();
            }
            catch(OutOfRangeExceptions e)
            {
                std::cout << e.what() << "\n";
                this->field = createField();
            }
        }
        this->field->create_Landscape();
        this->field->show_Landscape();
        //this->field->create_Neutral(1,1,'M');
        //this->field->create_Neutral(1,2,'V');
        //this->field->create_Neutral(1,3,'W');
        //this->field->create_Neutral(1,4,'A');
        this->field->show_Neutral();
        this->field->print_field();
        return this->field;

    }

    void handle(const std::string command, ChainOfRespons* chainofrespons, int* counturns) override
    {
        currstate->handle(command, chainofrespons);
        if (command == "attack" || command == "move" || command == "create")
        {
            changeState();
            counturns++;
        }
    }

    int defeat(int countofturns) override
    {

        if((this->field->getCountofDefA() > this->field->getCountofDefH() && countofturns > 50) || !this->field->checkABaseLose())
        {
            cout << "Aliens are defeated!";
            return 0;
        }
        else if((this->field->getCountofDefA() < this->field->getCountofDefH() && countofturns > 50) || !this->field->checkHBaseLose())
        {
            cout << "Humans are defeated!";
            return 1;
        }
        else
            return -1;
    }
};

class LongGameRule: public Rule
{
public:
    Field* createField() override
    {
        this->field = new Field(20, 20);
        while(!field->checkAleinBase() || !field->checkHumanBase())
        {
            try
            {
                Command* createbases = new CreateBaseComm(this->field);
                createbases->execute();
            }
            catch(LogicalExceptions e)
            {
                std::cout << e.what() << "\n";
                this->field = createField();
            }
            catch(TypeExceptions e)
            {
                std::cout << e.what() << "\n";
                this->field = createField();
            }
            catch(OutOfRangeExceptions e)
            {
                std::cout << e.what() << "\n";
                this->field = createField();
            }
        }
        this->field->create_Landscape();
        this->field->show_Landscape();
        this->field->print_field();
        return this->field;

    }

    void handle(const std::string command, ChainOfRespons* chainofrespons, int* counturns) override
    {
        currstate->handle(command, chainofrespons);
        if (command == "attack" || command == "move" || command == "create")
        {
            changeState();
            counturns++;
        }
    }

    int defeat(int countofturns) override
    {

        if(!this->field->checkABaseLose())
        {
            cout << "Aliens are defeated!";
            return 0;
        }
        else if(!this->field->checkHBaseLose())
        {
            cout << "Humans are defeated!";
            return 1;
        }
        else
            return -1;
    }
};


#endif // RULES_H
