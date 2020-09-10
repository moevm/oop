#ifndef COMMAND_H
#define COMMAND_H
#include "field.h"
#include "mediator.h"
#include "logging.h"
#include "snapshot.h"
#include "myexeptions.h"
#include <iostream>

class Command
{
public:
    virtual ~Command() {}
    virtual void execute() = 0;
    Command(Field* field) : field(field) {}
    Command(Field* field, char base) : field(field), base(base) {}
    Command(Field* field, Snapshot* snapshot) : field(field), snapshot(snapshot) {}
    Command(Field* field, Mediator* mediator) : field(field), mediator(mediator) {}
    Command(Field* field, Mediator* mediator, char base) : field(field), mediator(mediator), base(base) {}
    Command(Field* field, string input): field(field), input(input){}
protected:
    Field* field;
    string input;
    Mediator* mediator;
    Snapshot* snapshot;
    char base;
};

class SaveComm:public Command
{
public:
    SaveComm(Field* field, Snapshot* snapshot): Command(field, snapshot){}
    void execute() override
    {
        try
        {
            cout << "Saving game...\n";
            snapshot->saveGame();
        }
        catch(LogicalExceptions e)
        {
            std::cout << e.what() << "\n";
            return;
        }
        cout << "Game saved!\n";
    }
};

class LoadComm:public Command
{
public:
    LoadComm(Field* field, Snapshot* snapshot): Command(field, snapshot){}
    void execute() override
    {
        try
        {
            cout << "Loading game...\n";
            snapshot->loadGame();
        }
        catch(LogicalExceptions e)
        {
            std::cout << e.what() << "\n";
            return;
        }
        cout << "Game loaded!\n";
    }
};

class CreateBaseComm : public Command
{
public:
    CreateBaseComm(Field* field) : Command(field){}
    void execute()override
    {
        int max_count, health;
        string max_count_str, health_str;
        string typeOfBase;
        if (!(field->checkAleinBase()) || !(field->checkHumanBase()))
        {            
            cout << "Please, chose type of base to create:\n";
            cout << "Type A to create Alien base\n";
            cout << "Type H to create Human base\n";
            cin >> typeOfBase;
            cout << "Enter max units count: ";
            cin >> max_count_str;
            cout << "\nEnter base health: ";
            cin >> health_str;
            try
            {
                max_count = stoi(max_count_str);
                health = stoi(health_str);
            }
            catch (exception)
            {
                throw TypeExceptions("CreateBaseComm", "int");
            }
            if(health < 0)
            {
                throw LogicalExceptions("CreateBaseComm", health_str, "health < 0");
            }
            if(max_count < 0)
            {
                throw LogicalExceptions("CreateBaseComm", max_count_str, "maxcount < 0");
            }
            if(typeOfBase == "A")
                field->create_ABase(max_count,health);
            else if(typeOfBase == "H")
                field->create_HBase(max_count,health);
            else
            {
                throw LogicalExceptions("CreateBaseComm", typeOfBase , "A or H");
            }
        }
        else
        {
            cout << "Human Base and Alien Base are already on the Field\n";
        }
    }
};


class CreateUnitComm : public Command
{
public:
    CreateUnitComm(Field* field, char base) : Command(field, base){}
    void execute()
    {
        char typeOfUnit;

        if(base == 'A' && field->getIsAMaxCount())
        {
            cout << "Please, chose type of unit to:\n";
            cout << "Type S to create StormTrooper\n";
            cout << "Type D to create Droid\n";
            cout << "Type P to create PlasmaTank\n";

            cin >> typeOfUnit;
            this->field->createAUnit(typeOfUnit);
        }
        else if(base == 'H' && field->getIsHMaxCount())
        {
            cout << "Please, chose type of unit to:\n";
            cout << "Type S to create StormTrooper\n";
            cout << "Type D to create Droid\n";
            cout << "Type P to create PlasmaTank\n";

            cin >> typeOfUnit;
            this->field->createHUnit(typeOfUnit);
        }
        else if(base != 'A' && base != 'H')
        {
            throw LogicalExceptions("CreateUnitComm", &base, "A or H");
        }
    }
};

class MoveUnitComm : public Command
{
public:
    MoveUnitComm(Field* field, char base) : Command(field, base){
    }
    void execute() override
    {
        char wayToMove;
        Unit* currUnit = nullptr;     
        cout << "Choose way to move:\n";
        cout << "w to go up,\na to go left,\nd to go right,\ns to go down\n";
        cin >> wayToMove;
        if(base == 'A')
        {
            currUnit = field->getAChoosen();
            if(currUnit == nullptr)
                return;
            field->moveAUnit(wayToMove,currUnit);

        }
        else if(base == 'H')
        {
            currUnit = field->getHChoosen();
            if(currUnit == nullptr)
                return;
            field->moveHUnit(wayToMove,currUnit);
        }
        else
        {
            throw LogicalExceptions("MoveUnitComm", &base, "A or H");
        }
    }
};

class BaseStatusComm : public Command
{

    int baseNumb;
    Base* currBase;

public:
    BaseStatusComm(Field* field, char base) : Command(field, base){}
    void execute() override
    {
        Base* bbase = nullptr;
        if(base == 'A')
        {
            bbase = field->getABase();
        }
        else if(base == 'H')
        {
            bbase = field->getHBase();
        }
        else
        {
            throw LogicalExceptions("BaseStatusComm", &base, "A or H");
        }
        if(bbase == nullptr)
            return;
        cout << base << " Base:\n";
        cout << "Base Health:" << bbase->getHealth() << '\n';
        cout << "Base Max count of units:" << bbase->getMaxUnits() << '\n';
        cout << "Base current count of units:" << bbase->getCurrUnits() << '\n';
    }
};

class AttackComm : public Command
{

    Unit* currUnit;

public:
    AttackComm(Field* field, Mediator* mediator, char base) : Command(field, mediator, base){}
    void execute() override
    {
        char wayToAttack;
        Base* bbase = nullptr;
        if(base == 'A')
        {
            bbase = field->getABase();
            currUnit = field->getAChoosen();
        }
        else if(base == 'H')
        {
            bbase = field->getHBase();
            currUnit = field->getHChoosen();
        }
        else
        {
            throw LogicalExceptions("AttackComm", &base, "A or H");
        }
        if(bbase == nullptr || currUnit == nullptr)
            return;
        cout << "Choose way to attack:\n";
        cout << "w to up,\na to left,\nd to right,\ns to down\n";
        cin >> wayToAttack;
        if(wayToAttack == 'w')
        {
            mediator->attack(currUnit, currUnit->getX(),currUnit->getY() + 1);
        }
        else if(wayToAttack == 'a')
        {
           mediator->attack(currUnit, currUnit->getX() + 1,currUnit->getY());
        }
        else if(wayToAttack == 'd')
        {
           mediator->attack(currUnit, currUnit->getX() - 1,currUnit->getY());
        }
        else if(wayToAttack == 's')
        {
           mediator->attack(currUnit, currUnit->getX(),currUnit->getY() - 1);
        }
        else
        {
            throw LogicalExceptions("AttackComm", &wayToAttack, "w, a, d or s");
        }
    }
};

class NextComm : public Command
{
    public:
    NextComm(Field* field, char base) : Command(field, base) {}
    void execute() override
    {
        Unit* currUnit = nullptr;
        Unit* newcurrUnit = nullptr;

        if(base == 'A')
        {
            currUnit = field->getAChoosen();
        }
        else if(base == 'H')
        {
            currUnit = field->getHChoosen();
        }
        else
        {
            throw LogicalExceptions("NextComm", &base, "A or H");
        }
        if(currUnit == nullptr)
            return;
        currUnit->setChoose(false);
        for (int i = currUnit->getX() + 1; i < field->getX(); i++)
        {
            newcurrUnit = field->getUnit(i,currUnit->getY());
            if(newcurrUnit != nullptr)
            {
                if(newcurrUnit->getArmy() == base)
                {
                    cout << "Current unit on position: " << "(" << i << "," << currUnit->getY() << ")\n";
                    newcurrUnit->setChoose(true);
                    return;
                }
            }
        }
        for (int j = currUnit->getY() + 1; j < field->getY(); j++)
        {
            for (int i = 0; i < field->getX(); i++)
            {
                newcurrUnit = field->getUnit(i,j);
                if(newcurrUnit != nullptr)
                {
                    if(newcurrUnit->getArmy() == base)
                    {
                        cout << "Current unit on position: " << "(" << i << "," << j << ")\n";
                        newcurrUnit->setChoose(true);
                        return;
                    }
                }
                if(j == field->getY() - 1 && i == field->getX() - 1)
                {                    
                    i = 0;
                    j = 0;
                }
            }
        }
    }
};

class LoggingComm: public Command
{
public:
    LoggingComm(Field* field) : Command(field) {}
    void execute() override
    {
        string input;
        cout << "logging? off/console/file\n";
        cin  >> input;
        if(input == "off")
        {
            LoggingProxy::logOff();
            cout << "logging off\n";
        }
        else if(input == "console")
        {
            LoggingProxy::logToConsole();
            cout << "switch to log in console\n";
        }
        else if(input == "file")
        {
            LoggingProxy::logToFile();
            cout << "switch to log in file";
        }
        else
        {
            throw LogicalExceptions("LoggingComm", input, "off, console or file");
        }
    }
};



#endif // COMMAND_H
