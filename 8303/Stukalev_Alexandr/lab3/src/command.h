#ifndef COMMAND_H
#define COMMAND_H
#include "field.h"
#include "mediator.h"
#include <iostream>
class Command
{
public:
    virtual ~Command() {}
    virtual void execute() = 0;
    Command(Field* field) : field(field) {}
    Command(Field* field, Mediator* mediator) : field(field), mediator(mediator) {}
protected:
    Field* field;
    Mediator* mediator;
};
class CreateBaseComm : public Command
{
public:
    CreateBaseComm(Field* field) : Command(field){}
    void execute()override
    {
        int max_count, health;
        char typeOfBase;
        if (!(field->checkAleinBase()) || !(field->checkHumanBase()))
        {            
            cout << "Please, chose type of base to create:\n";
            cout << "Type A to create Alien base\n";
            cout << "Type H to create Human base\n";
            cin >> typeOfBase;
            cout << "Enter max units count: ";
            cin >> max_count;
            cout << "\nEnter base health: ";
            cin >> health;
            if(typeOfBase == 'A')
                field->create_ABase(max_count,health);
            if(typeOfBase == 'H')
                field->create_HBase(max_count,health);
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
    CreateUnitComm(Field* field) : Command(field){}
    void execute()
    {
        char typeOfBase;
        char typeOfUnit;
        cout << "Please, chose type of base to create unit:\n";
        cout << "Type A to create Alien unit\n";
        cout << "Type H to create Human unit\n";
        cin >> typeOfBase;

        if(typeOfBase == 'A' && field->getIsAMaxCount())
        {
            cout << "Please, chose type of unit to:\n";
            cout << "Type S to create StormTrooper\n";
            cout << "Type D to create Droid\n";
            cout << "Type P to create PlasmaTank\n";

            cin >> typeOfUnit;
            this->field->createAUnit(typeOfUnit);
        }
        if(typeOfBase == 'H' && field->getIsHMaxCount())
        {
            cout << "Please, chose type of unit to:\n";
            cout << "Type S to create StormTrooper\n";
            cout << "Type D to create Droid\n";
            cout << "Type P to create PlasmaTank\n";

            cin >> typeOfUnit;
            this->field->createHUnit(typeOfUnit);
        }
    }
};

class MoveUnitComm : public Command
{
public:
    MoveUnitComm(Field* field) : Command(field){
    }
    void execute() override
    {
        char typeOfBase;
        char wayToMove;
        Unit* currUnit = nullptr;
        cout << "Please, chose type of base to move unit:\n";
        cout << "Type A to choose Alien base\n";
        cout << "Type H to choose Human base\n";
        cin >> typeOfBase;       
        cout << "Choose way to move:\n";
        cout << "w to go up,\na to go left,\nd to go right,\ns to go down\n";
        cin >> wayToMove;
        if(typeOfBase == 'A')
        {
            currUnit = field->getAChoosen();
            if(currUnit == nullptr)
                return;
            field->moveAUnit(wayToMove,currUnit);

        }
        if(typeOfBase == 'H')
        {
            currUnit = field->getHChoosen();
            if(currUnit == nullptr)
                return;
            field->moveHUnit(wayToMove,currUnit);
        }
    }
};

class BaseStatusComm : public Command
{

    int baseNumb;
    Base* currBase;

public:
    BaseStatusComm(Field* field) : Command(field){}
    void execute() override
    {
        char typeOfBase;
        Base* base = nullptr;
        cout << "Please, chose type of base to show status:\n";
        cout << "Type A to show Alien base status\n";
        cout << "Type H to show Human base status\n";
        cin >> typeOfBase;
        if(typeOfBase == 'A')
        {
            base = field->getABase();
        }
        if(typeOfBase == 'H')
        {
            base = field->getHBase();
        }
        if(base == nullptr)
            return;
        cout << typeOfBase << " Base:\n";
        cout << "Base Health:" << base->getHealth() << '\n';
        cout << "Base Max count of units:" << base->getMaxUnits() << '\n';
        cout << "Base current count of units:" << base->getCurrUnits() << '\n';
    }
};

class AttackComm : public Command
{

    Unit* currUnit;

public:
    AttackComm(Field* field, Mediator* mediator) : Command(field, mediator){}
    void execute() override
    {
        char typeOfBase;
        char wayToAttack;
        Base* base = nullptr;
        cout << "Please, chose type of base to units attack:\n";
        cout << "Type A to choose Alien base\n";
        cout << "Type H to choose Human base\n";
        cin >> typeOfBase;
        if(typeOfBase == 'A')
        {
            base = field->getABase();
            currUnit = field->getAChoosen();
        }
        if(typeOfBase == 'H')
        {
            base = field->getHBase();
            currUnit = field->getHChoosen();
        }
        if(base == nullptr || currUnit == nullptr)
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
    }
};

class NextComm : public Command
{
    public:
    NextComm(Field* field) : Command(field) {}
    void execute() override
    {
        char typeOfBase;
        Unit* currUnit = nullptr;
        Unit* newcurrUnit = nullptr;
        cout << "Please, chose type of base to select next Unit:\n";
        cout << "Type A to choose Alien base\n";
        cout << "Type H to choose Human base\n";
        cin >> typeOfBase;
        if(typeOfBase == 'A')
        {
            currUnit = field->getAChoosen();
        }
        if(typeOfBase == 'H')
        {
            currUnit = field->getHChoosen();
        }
        if(currUnit == nullptr)
            return;
        currUnit->setChoose(false);
        for (int i = currUnit->getX() + 1; i < field->getX(); i++)
        {
            newcurrUnit = field->getUnit(i,currUnit->getY());
            if(newcurrUnit != nullptr)
            {
                if(newcurrUnit->getArmy() == typeOfBase)
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
                    if(newcurrUnit->getArmy() == typeOfBase)
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
#endif // COMMAND_H
