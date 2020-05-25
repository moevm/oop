#ifndef GAMECLASS_H
#define GAMECLASS_H

#include "rules.h"



template <typename T>
class GameSingltone
{
protected:
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
    GameSingltone()
    {
        /*rule = new Rules();
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
        this->chainOfRespons->addToChain(elemWrongComm);*/

    }

    int playGame()
    {

    }

};

template <typename Rules>
class Game: public GameSingltone<Rules>{

};

template <>
class Game<LongGameRule>: public GameSingltone<LongGameRule>{
    LongGameRule* longGameRule;
    static Game<LongGameRule> *game;
    Game<LongGameRule>()
    {

    }
public:
    static Game<LongGameRule>* getInstance()
    {
        if (game == nullptr){
            game = new Game<LongGameRule>;
        }
        return game;
    }
    void createGame()
    {
        longGameRule = new LongGameRule;
        this->field = longGameRule->createField();
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
            wholose = longGameRule->defeat(countofturns);
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
            longGameRule->handle(cmd, chainOfRespons, &countofturns);
        }
    }
};

template<>
class Game<ShortGameRule>: public GameSingltone<ShortGameRule>
{
    ShortGameRule* shortGameRule;
    static Game<ShortGameRule> *game;
    Game<ShortGameRule>()
    {

    }
public:
    static Game<ShortGameRule>* getInstance()
    {
        if (game == nullptr)
        {
            game = new Game<ShortGameRule>;
        }
        return game;
    }
    void createGame()
    {
        shortGameRule = new ShortGameRule;
        this->field = shortGameRule->createField();
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
            wholose = shortGameRule->defeat(countofturns);
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
            shortGameRule->handle(cmd, chainOfRespons, &countofturns);
        }
    }
};









#endif // GAMECLASS_H
