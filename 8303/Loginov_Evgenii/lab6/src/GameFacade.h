#ifndef GAMEFACADE_H
#define GAMEFACADE_H
#ifndef FACADE_H
#define FACADE_H

#include "Field.h"
#include "ChainOfCommand.h"
#include "adapter.h"

#include "Rules.h"

template <typename T>
class GameFacade
{
private:
    T rule;
    Field *field;

    chainOfResponsibility *basecomm;
    Adapter* adapter;
public:
    GameFacade() {
        adapter = new Adapter();
    }

    void createField();
    void play();

    ~GameFacade() {
        delete adapter;
    }

};

template <typename T>
void GameFacade<T>::createField()
{
    std::cout<<"< field creating: >\n";
    field = rule.createField(adapter);

    basecomm = new chainOfResponsibility();

    basecomm->add(new createBaseCor(field));
    basecomm->add(new SwitchLogCor(field));
    basecomm->add(new baseInfoCor(field));
    basecomm->add(new createUnitCor(field));
    basecomm->add(new moveUnitCor(field));

    basecomm->add(new saveCor(field));
    basecomm->add(new loadCor(field));
    basecomm->add(new uknownCmdCor);
}

template <typename T>
void GameFacade<T>::play()
{
    std::cout << "Game started" << std::endl;
    std::string commandStr;
    field->print();

    int res = -1;
    while (res < 0){
        rule.printState();

        std::cin >> commandStr;

        if(commandStr=="exit") {
            std::cout << "Bye!";
            break;
        }

        if(commandStr=="newGame") {
            delete field;
            createField();
        }
        else {
            rule.handle(commandStr, basecomm); // обработка команды
        }

        field->print();
        res = rule.isLose(field);
    }

    std::cout << "Game over" << std::endl;
    if(res==0)
        std::cout << "Player 1 won!" << std::endl;
    else if(res==1){
        std::cout << "Player 2 won!" << std::endl;
    }
    else {
        std::cout << "Draw!" << std::endl;
    }
}


#endif // FACADE_H

#endif // GAMEFACADE_H
