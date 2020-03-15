#ifndef OOP1_COMMAND_H
#define OOP1_COMMAND_H

#include "Field.h"
#include "Mediator.h"

class BaseCommand{
public:
    virtual void execute() = 0;
protected:
    BaseCommand(Field* field): field(field) {}
    Field* field;
};

class SetBaseCommand: public BaseCommand{
private:
    int x, y, maxCount, health;
public:
    SetBaseCommand(Field* field) : BaseCommand(field) {
    }
        void execute() override{
            std::cout << "Set x of base:" << std::endl;
            std::cin >> x;
            std::cout << "Set y of base: "<< std::endl;
            std::cin >> y;
            std::cout << "Set maximum count unit of base: "<< std::endl;
            std::cin >> maxCount;
            std::cout << "Set  health of base: "<< std::endl;
            std::cin >> health;
            std::cout << std::endl;
            field->createBase(x, y, maxCount, health);
        }
};

class AttackUnitCommand: public BaseCommand{
private:
    int number;
    Unit* current;
    std::string command;
public:
    AttackUnitCommand(Field* field, Mediator* mediator) : BaseCommand(field) {
    }
    void execute() override{
        std::cout << "Choose the number base" << std::endl;
        std::cin >> number;

        if (number <= 0 || number > 2){
            std::cout << "Incorrect number base"<<std::endl;
            return;
        }

        if (number == 1)
            current = field->base1->getUnit();
        else
            current = field->base2->getUnit();

        while(true){
            std::cout << "Unit "<< current->name << " x: " << field->findUnit(current)->x << " y: " << field->findUnit(current)->y <<std::endl;
            std::cin >> command;
            if (command == "n") {
                if (number==1)
                    current = field->base1->getUnit();
                else
                    current = field->base2->getUnit();
            }
            else if (command == "w"){
                if (current->name == 's' || current->name == 'k')
                    current->mediator->attack(current, field->findUnit(current)->x, field->findUnit(current)->y - 2);
                else
                    current->mediator->attack(current, field->findUnit(current)->x, field->findUnit(current)->y - 1);
                break;
            }
            else if (command == "s"){
                if (current->name == 's' || current->name == 'k')
                    current->mediator->attack(current, field->findUnit(current)->x, field->findUnit(current)->y - 2);
                else
                    current->mediator->attack(current, field->findUnit(current)->x, field->findUnit(current)->y - 1);
                break;
            }
            else if (command == "a"){
                if (current->name == 's' || current->name == 'k')
                    current->mediator->attack(current, field->findUnit(current)->x - 2, field->findUnit(current)->y);
                else
                    current->mediator->attack(current, field->findUnit(current)->x - 1, field->findUnit(current)->y);
                break;
            }
            else if (command == "d"){
                if (current->name == 's' || current->name == 'k')
                    current->mediator->attack(current, field->findUnit(current)->x + 2, field->findUnit(current)->y);
                else
                    current->mediator->attack(current, field->findUnit(current)->x + 1, field->findUnit(current)->y);
                break;
            }
        }


    }
};

class StatusBaseCommand: public BaseCommand{
private:
    int number;
public:
    StatusBaseCommand(Field* field) : BaseCommand(field) {
    }
    void execute() override{
        std::cout << "Choose the number base" << std::endl;
        std::cin >> number;

        if (number <= 0 || number > 2){
            std::cout << "Incorrect number base"<<std::endl;
            return;
        }

        if (number == 1){
            std::cout << "Base number 1" <<std::endl;
            std::cout << "x: " << field->base1->BaseX << "  y: " << field->base1->BaseY << std::endl;
            std::cout << "Health: " << field->base1->health << std::endl;
            std::cout << "MaxCountUnit: " << field->base1->maxCountUnit << std::endl;
            std::cout << "Count unit: " << field->base1->countUnit << std::endl;
            std::cout << "Units of base: " << std::endl;
            field->base1->printUnit();
        }
        else{
            std::cout << "Base number 2" <<std::endl;
            std::cout << "x: " << field->base2->BaseX << "  y: " << field->base2->BaseY << std::endl;
            std::cout << "Health: " << field->base2->health << std::endl;
            std::cout << "MaxCountUnit: " << field->base2->maxCountUnit << std::endl;
            std::cout << "Count unit: " << field->base2->countUnit << std::endl;
            std::cout << "Units of base: " << std::endl;
            field->base2->printUnit();
        }



    }
};

class MoveUnitCommand: public BaseCommand{
private:
    int number;
    std::string command;
    Unit* current;
public:
    MoveUnitCommand(Field* field) : BaseCommand(field) {
    }
    void execute() override{
        std::cout << "Choose the number base" << std::endl;
        std::cin >> number;

        if (number <= 0 || number > 2){
            std::cout << "Incorrect number base"<<std::endl;
            return;
        }

        if (number == 1)
            current = field->base1->getUnit();
        else
            current = field->base2->getUnit();

            while(true){
                std::cout << "Unit "<< current->name << " x: " << field->findUnit(current)->x << " y: " << field->findUnit(current)->y <<std::endl;
                std::cin >> command;
                if (command == "n") {
                    if (number==1)
                        current = field->base1->getUnit();
                    else
                        current = field->base2->getUnit();
                }
                else if (command == "w"){
                    field->moveUnitUp(current);
                    break;
                }
                else if (command == "s"){
                    field->moveUnitDown(current);
                    break;
                }
                else if (command == "a"){
                    field->moveUnitLeft(current);
                    break;
                }
                else if (command == "d"){
                    field->moveUnitRight(current);
                    break;
                }
            }
        }
};

class CreateUnitCommand: public BaseCommand{
private:
    int number;
    char character;
    Mediator* mediator;
public:
    CreateUnitCommand(Field* field, Mediator* mediator) : BaseCommand(field), mediator(mediator) {
    }
    void execute() override{
        std::cout << "Choose the number base" << std::endl;
        std::cin >> number;

        if (number <= 0 || number > 2){
            std::cout << "Incorrect number base"<<std::endl;
            return;
        }

        if (number == 1) {
            int capacity = field->base1->getCapacityUnit();
            for (int i = 0; i < capacity; i++) {
                std::cout << "Enter name of unit" << std::endl;
                std::cin >> character;
                if (!field->base1->createUnit(character, mediator)){
                    std::cout << "The area near base is limited" << std::endl;
                    break;
                }
            }
            std::cout << "Units has been set"<<std::endl;
        }

        else{
            int capacity = field->base2->getCapacityUnit();
            for (int i = 0; i < capacity; i++) {
                std::cout << "Enter name of unit" << std::endl;
                std::cin >> character;
                if (!field->base2->createUnit(character, mediator)){
                    std::cout << "The area near base is limited" << std::endl;
                    break;
                }
            }
            std::cout << "Units has been set"<<std::endl;
        }

    }
};


#endif //OOP1_COMMAND_H
