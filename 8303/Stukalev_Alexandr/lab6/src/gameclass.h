#ifndef GAMECLASS_H
#define GAMECLASS_H

#include "rules.h"



template <class Rules>
class Game
{
private:
    Rules* rule;
    int wholose;
    int countofturns;
    std::string cmd;
    Field* field;
    ChainOfRespons* chainOfRespons;
    ElemUnitMove* elemUnitMove;
    ElemUnitCreat* elemUnitCreate;
    ElemUnitAttack* elemUnitAttack;
    ElemBaseStatus* elemBaseStatus;
    ElemLogging* elemLogging;
    ElemWrongComm* elemWrongComm;
    ElemLoadComm* elemLoadComm;
    ElemSaveComm* elemSaveComm;
    ElemNextComm* elemNextComm;
    Snapshot* snapshot;
public:
    Game()
    {
        rule = new Rules();
        this->field = rule->createField();

        this->countofturns = 0;

        snapshot = new Snapshot(this->field);
        this->chainOfRespons = new ChainOfRespons();

        this->elemUnitCreate = new ElemUnitCreat(field);
        this->chainOfRespons->addToChain(elemUnitCreate);

        this->elemUnitMove = new ElemUnitMove(field);
        this->chainOfRespons->addToChain(elemUnitMove);

        this->elemUnitAttack = new ElemUnitAttack(field);
        this->chainOfRespons->addToChain(elemUnitAttack);

        this->elemBaseStatus = new ElemBaseStatus(field);
        this->chainOfRespons->addToChain(elemBaseStatus);

        this->elemNextComm = new ElemNextComm(field);
        this->chainOfRespons->addToChain(elemNextComm);

        this->elemLogging = new ElemLogging(field);
        this->chainOfRespons->addToChain(elemLogging);

        this->elemLoadComm = new ElemLoadComm(field);
        this->chainOfRespons->addToChain(elemLoadComm);

        this->elemSaveComm = new ElemSaveComm(field);
        this->chainOfRespons->addToChain(elemSaveComm);

        this->elemWrongComm = new ElemWrongComm();
        this->chainOfRespons->addToChain(elemWrongComm);

    }

    int playGame()
    {
        while(cmd != "end")
        {
            wholose = rule->defeat(countofturns);
            if(wholose == 0)
            {
                cout << "Human win!\n";
                return 0 ;
            }
            else if(wholose == 1)
            {
                cout << "Alien win!\n";
                return 1;
            }
            cin >> cmd;

            if( cmd == "new")
            {
                cout << "New game started...\n";
                return -1;
            }
            rule->handle(cmd, chainOfRespons, &countofturns);
        }
    }

};










#endif // GAMECLASS_H
