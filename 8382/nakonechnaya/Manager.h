#ifndef OOP_MANAGER_H
#define OOP_MANAGER_H
#include <iostream>
#include <map>
#include <vector>
#include "Commands/StartGameCommand.h"
#include "Commands/CreateUnitCommand.h"
#include "Commands/DeleteUnitCommand.h"
#include "Commands/MoveUnitCommand.h"
#include "Commands/AttackUnitCommand.h"
#include "Commands/UnitsAttributesCommand.h"
#include "Commands/ActionWithObjectCommand.h"
#include "Commands/AttackBaseCommand.h"
#include "Memento.h"

class Manager {
public:
    explicit Manager(){
        srand(time(NULL));
        gameField = new GameField;
        proxy = nullptr;
    };
    void startGame(Rules *rules);
    void setBases();
    void printField();
    void printMenu();
    void makeChoice();
    void createGamer();
    void setLogger();
    void loadGame(Memento *memento, bool first);
    void saveGame();
    bool checkWin(int, int);
private:
    GameField *gameField;
    std::map<Gamer*, Base*> bases;
    std::map<int, Gamer*> gamers;
    StartGameCommand *startCommand;
    CreateUnitCommand *createUnitCommand;
    DeleteUnitCommand *deleteUnitCommand;
    MoveUnitCommand *moveUnitCommand;
    AttackUnitCommand *attackUnitCommand;
    UnitsAttributesCommand *unitsAttributesCommand;
    ActionWithObjectCommand *actionWithObjectCommand;
    AttackBaseCommand *attackBaseCommand;
    LogProxy *proxy;
    std::vector<Memento*> mementos;
    Rules *rules;
};
#endif //OOP_MANAGER_H
