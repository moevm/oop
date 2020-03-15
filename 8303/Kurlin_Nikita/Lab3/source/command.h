#ifndef COMMAND_H
#define COMMAND_H

#include "gamefield.h"
#include "mediator.h"

using namespace std;

class Command{

public:
    virtual ~Command() {}
    virtual void execute() = 0;
    Command(GameField* field) : field(field) {}
    Command(GameField* field, Mediator* mediator) : field(field), mediator(mediator) {}

protected:
    GameField* field;
    Mediator* mediator;
};

class CreateBaseCommand : public Command{

public:
    CreateBaseCommand(GameField* field) : Command(field){}
    void execute() override{
        int maxUnitsCount, health, x, y;

        if ((field->base1 == nullptr) || (field->base2 == nullptr)){
            cout << "Enter max units count: ";
            cin >> maxUnitsCount;
            cout << "Enter base health: ";
            cin >> health;
            cout << "Enter x and y coordinates of base: ";
            cin >> x >> y;
            getchar();
            field->setBase(maxUnitsCount, health, x, y);
        }
        else {
            cout << "There are two base already\n";
        }
    }
};


class CreateUnitCommand : public Command{

    int baseNumb;

public:
    CreateUnitCommand(GameField* field, Mediator* mediator) : Command(field, mediator){}
    void execute() override{
        cout << "Choose base for creating unit (1 or 2) ";
        cin >> baseNumb;
        getchar();

        if (baseNumb == 1 || baseNumb == 2){
            int n = (baseNumb == 1) ? field->base1->getCapacityCount() : field->base2->getCapacityCount();
            if (n == 0)
                cout << "Max count of unit on base\n";

            for (int i = 0; i < n; i++){
                cout << "Enter unit's type: ";
                string unitName;
                getline(cin, unitName);
                if ((baseNumb == 1) ? field->createUnit(unitName, field->base1, mediator) == 0 : field->createUnit(unitName, field->base2, mediator) == 0)
                    return;
            }
        }
        else {
            cout << "Wrong numb of base\n";
        }
    }
};

class MoveUnitCommand : public Command{

    int baseNumb;
    Unit* currUnit;
    Point* currPoint;

public:
    MoveUnitCommand(GameField* field) : Command(field){}
    void execute() override{
        cout << "Choose base for moving unit (1 or 2) ";
        cin >> baseNumb;
        getchar();

        Base* base = (baseNumb == 1) ? field->base1 : field->base2;
        if (baseNumb == 1 || baseNumb == 2){
            while(true){
                currUnit = (baseNumb == 1) ? field->base1->getCurrUnit() : field->base2->getCurrUnit();
                currPoint = field->findUnit(currUnit);
                cout << currUnit->armyType << " (" << currPoint->x << ";" << currPoint->y << ") ? ";

                string str;
                getline(cin, str);

                if(str == "n")
                    continue;
                else{
                    if(str == "w")
                        field->moveUnitUp(currUnit, base);
                    else if(str == "s")
                        field->moveUnitDown(currUnit, base);
                    else if(str == "a")
                        field->moveUnitLeft(currUnit, base);
                    else if(str == "d")
                        field->moveUnitRight(currUnit, base);
                    else{
                        cout << "Wrong command for moving\n";
                        return;
                    }
                    break;
                }
            }
        }
        else {
            cout << "Wrong numb of base\n";
        }
    }
};

class BaseStatusCommand : public Command{

    int baseNumb;
    Base* currBase;

public:
    BaseStatusCommand(GameField* field) : Command(field){}
    void execute() override{
        cout << "Choose base for status (1 or 2) ";
        cin >> baseNumb;
        getchar();

        if (baseNumb == 1 || baseNumb == 2){
            currBase = (baseNumb == 1) ? field->base1 : field->base2;
            cout << "Base " << baseNumb << " (" << currBase->x << ";" << currBase->y << ")\n";
            cout << "*Health " << currBase->health << endl;
            cout << "*Current count of units on field / Max count on base: " << currBase->unitCount << "/" << currBase->maxCount << endl;
            currBase->printAll();
        }
        else {
            cout << "Wrong numb of base\n";
        }
    }
};

class AttackCommand : public Command{

    int baseNumb;
    Unit* currUnit;
    Point* currPoint;

public:
    AttackCommand(GameField* field, Mediator* mediator) : Command(field, mediator){}
    void execute() override{
        cout << "Choose base for attack (1 or 2) ";
        cin >> baseNumb;
        getchar();

        Base* base = (baseNumb == 1) ? field->base1 : field->base2;
        if (baseNumb == 1 || baseNumb == 2){
            while(true){
                currUnit = (baseNumb == 1) ? field->base1->getCurrUnit() : field->base2->getCurrUnit();
                currPoint = field->findUnit(currUnit);
                cout << currUnit->armyType << " (" << currPoint->x << ";" << currPoint->y << ") ? ";

                string str;
                getline(cin, str);

                if(str == "n")
                    continue;
                else{
                    if(str == "w")
                        currUnit->mediator->attack(currUnit, currPoint->x, (currUnit->armyType == "Archer") ? currPoint->y - 2 : currPoint->y - 1);
                    else if(str == "s")
                        currUnit->mediator->attack(currUnit, currPoint->x, (currUnit->armyType == "Archer") ? currPoint->y + 2 : currPoint->y + 1);
                    else if(str == "a")
                        currUnit->mediator->attack(currUnit, (currUnit->armyType == "Archer") ? currPoint->x - 2 : currPoint->x - 1, currPoint->y);
                    else if(str == "d")
                        currUnit->mediator->attack(currUnit, (currUnit->armyType == "Archer") ? currPoint->x + 2 :currPoint->x + 1, currPoint->y);
                    else{
                        cout << "Wrong direction of attack\n";
                        return;
                    }
                    break;
                }
            }
        }
        else {
            cout << "Wrong numb of base\n";
        }
    }
};

#endif // COMMAND_H
