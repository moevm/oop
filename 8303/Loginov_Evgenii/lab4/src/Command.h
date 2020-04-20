#ifndef COMMAND_H
#define COMMAND_H

#include "Field.h"
#include "Base.h"

class Command{
public:
    virtual void execute() = 0;
protected:
    Adapter *adapter;
    Command(Field* field): field(field) {}
    Field* field;
};

class createBaseCommand : public Command{
private:
    int x, y, maxUnit, health;
public:
    createBaseCommand(Field* field) : Command(field) {
    }
    void execute() override{
        std::cout << "Set x of base:" << std::endl;
        std::cin >> x;
        std::cout << "Set y of base: "<< std::endl;
        std::cin >> y;
        std::cout << "Set maximum count unit of base: "<< std::endl;
        std::cin >> maxUnit;
        std::cout << "Set  health of base: "<< std::endl;
        std::cin >> health;
        std::cout << std::endl;
        field->createBase(x, y, maxUnit, health);
    }
};

class switchLogCommand : public Command {
private:
     std::string command;
public:
    switchLogCommand(Field* field) :Command (field){ }
    void execute() override{
        std::cout<<"choose command for log switch\n";
        std::cin >> command;
        if (command == "fileOff"){
            field->adapter->switchLog("fileOff");
        }
        else if(command == "fileOn") {
            field->adapter->switchLog("fileOn");
        }
        else if(command == "consoleOff"){
            field->adapter->switchLog("consoleOff");
        }
        else if(command == "consoleOn"){
            field->adapter->switchLog("consoleOn");
        }
        else{
            std::cout << "No exist this command for log" << std::endl;
            std::cout << "use: fileOff, fileOn, consoleOff, consoleOn" << std::endl;
        }
    }
};

class baseInfoCommand : public Command {
public:
    baseInfoCommand(Field* field) : Command(field) {
    }
    void execute() {
        Base *base = field->getBase();
        if(base)
            base->printInfo();
        else {
            std::cout << "There is not any base!" << std::endl;
        }
    }
};

class createUnitCommand : public Command {
public:
    createUnitCommand(Field* field) : Command(field) {
    }
    void execute() {
        std::cout << "CreateUnitCommand" << std::endl;

        Base *base = field->getBase();
        if(base) {
            std::cout << "which type of unit you want to create? ";
            char c;
            std::cin >> c;
            base->createUnit(c);
        }
        else {
            std::cout << "Can't create unit without base!" << std::endl;
        }
    }
};

class moveUnitCommand : public Command {
public:
    moveUnitCommand(Field* field) : Command(field) {
    }
    void execute() {
        std::cout << "MoveUnitCommand" << std::endl;

        Base *base = field->getBase();
        if(base!=nullptr && base->countAllUnits()>0) {
            base->printUnits();

            std::cout << "input # of unit to move: ";
            int id;
            std::cin >> id;

            std::cout << "input direction to move (wasd): ";
            char d;
            std::cin>>d;

            Unit *unit = base->getUnitById(id);
            int x = unit->getx();
            int y = unit->gety();

            switch(d) {
                case 'w': field->moveUnit(unit, x, y-1); break;
                case 'a': field->moveUnit(unit, x-1, y); break;
                case 's': field->moveUnit(unit, x, y+1); break;
                case 'd': field->moveUnit(unit, x+1, y); break;
            }
        }
        else {
            std::cout << "There is not any unit!" << std::endl;
        }
    }
};


class uknownCommand : public Command {
public:
    uknownCommand() : Command(nullptr){
    }
    void execute() {
        std::cout << "Uknown command!!!" << std::endl;
    }
};

#endif // COMMAND_H
