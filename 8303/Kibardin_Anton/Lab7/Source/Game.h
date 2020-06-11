//
// Created by anton on 05.05.2020.
//

#ifndef OOP_1_GAME_H
#define OOP_1_GAME_H

#include "Facade.h"
#include "Rules.h"

template<typename Rule> class GameBase {
protected:
    Field* field;
    Adapter* adapter;
    int loser;
    std::string command;

    BaseHandler* baseHandler;
    BaseHandler* setBaseHandler;
    BaseHandler* setUnitHandler;
    BaseHandler* moveUnitRightHandler;
    BaseHandler* moveUnitLeftHandler;
    BaseHandler* moveUnitUpHandler;
    BaseHandler* moveUnitDownHandler;
    BaseHandler* attackUnitHandler;
    BaseHandler* showStatusHandler;
    BaseHandler* helpHandler;
    BaseHandler* adapterHandler;
    BaseHandler* turnOnOffLog;
    BaseHandler* saveHandler;
    BaseHandler* loadHandler;
    BaseHandler* setTitanHandler;

    virtual void createGame(){
        baseHandler = new BaseHandler(field);
        setBaseHandler = new SetBaseHandler(field);
        setUnitHandler = new SetUnitHandler(field);
        moveUnitLeftHandler = new MoveUnitLeftHandler(field);
        moveUnitDownHandler = new MoveUnitDownHandler(field);
        moveUnitUpHandler = new MoveUnitUpHandler(field);
        moveUnitRightHandler = new MoveUnitRightHandler(field);
        attackUnitHandler = new AttackUnitHandler(field);
        showStatusHandler = new ShowStatusHandler(field);
        helpHandler = new HelpHandler(field);
        adapterHandler = new SwitchLogHandler(adapter);
        turnOnOffLog = new TurnOnOffLog(adapter);
        saveHandler = new SaveHandler(adapter, field);
        loadHandler = new LoadHandler(adapter, field);
        setTitanHandler = new SetTitanHandler(adapter, field);

        baseHandler->setNext(setBaseHandler);
        setBaseHandler->setNext(setUnitHandler);
        setUnitHandler->setNext(moveUnitRightHandler);
        moveUnitRightHandler->setNext(moveUnitUpHandler);
        moveUnitUpHandler->setNext(moveUnitDownHandler);
        moveUnitDownHandler->setNext(moveUnitLeftHandler);
        moveUnitLeftHandler->setNext(attackUnitHandler);
        attackUnitHandler->setNext(showStatusHandler);
        showStatusHandler->setNext(helpHandler);
        helpHandler->setNext(adapterHandler);
        adapterHandler->setNext(turnOnOffLog);
        turnOnOffLog->setNext(saveHandler);
        saveHandler->setNext(loadHandler);
        loadHandler->setNext(setTitanHandler);
    }

    void prepareGame(int playersNumber, std::string gameMode)
    {
        std::string mode = "prepare";
        try {
            std::cout << "Load game or new game?(load/new): " ;
            std::cin >> command;

            if(command != "new" && command != "load")
                throw LogicException("incorrect game choice",command);
            if (command == "load") {
                baseHandler->handle(command, playersNumber, mode);
            }
            else{
                if(gameMode == "baseDefence")
                    createBase(playersNumber);
                else
                    createTitans(playersNumber);
            }
        }catch (LogicException& exception) {
            std::cout << exception.what()<< std::endl;
            prepareGame(playersNumber, gameMode);
        } catch (TypeException& exception) {
            std::cout << exception.what() << std::endl;
            prepareGame(playersNumber, gameMode);
        } catch (CheckException& exception) {
            std::cout << exception.what() << std::endl;
            prepareGame(playersNumber, gameMode);
        }
    }

    void createBase(int countBase){
        field->printLandscape();
        field->printNeutrals();
        std::string command = "setBase";
        std::string mode = "prepare";
        std::cout << "User 1 set base: " << std::endl;
        baseHandler->handle(command, 1, mode);
        std::cout << "User 2 set base: " << std::endl;
        baseHandler->handle(command, 2, mode);
        if (countBase == 3) {
            std::cout << "User 3 set base: " << std::endl;
            baseHandler->handle(command, 3, mode);
        }
    }

    void createTitans(int countBase){
        try {
            field->printLandscape();
            field->printNeutrals();
            std::string command = "setTitan";
            std::string mode = "prepare";
            std::cout << "User 1 set Titan: " << std::endl;
            baseHandler->handle(command, 1, mode);
            std::cout << "User 2 set Titan: " << std::endl;
            baseHandler->handle(command, 2, mode);
            if (countBase == 3) {
                std::cout << "User 3 set Titan: " << std::endl;
                baseHandler->handle(command, 3, mode);
            }
        }catch (LogicException& exception) {
            std::cout << exception.what()<< std::endl;
            createTitans(countBase);
        } catch (TypeException& exception) {
            std::cout << exception.what() << std::endl;
            createTitans(countBase);
        } catch (CheckException& exception) {
            std::cout << exception.what() << std::endl;
            createTitans(countBase);
        }

    }
};

template<typename Rule, int>  class Game: public GameBase<Rule>{};

template<> class Game<Rule1, 2>: public GameBase<Rule1>
{
    Rule1* rule;
    static Game<Rule1, 2> *game;

    Game<Rule1, 2>(){}

public:

    static Game<Rule1, 2>* getInstance(){
        if (game == nullptr)
            game = new Game<Rule1, 2>;
        return game;
    }

    void createGame() override {
        adapter = new Adapter();
        rule = new Rule1();
        field = rule->createField(adapter);
        GameBase::createGame();
    }

    void play(){
        GameBase::prepareGame(2, "baseDefence");
        while (true) {
            loser = rule->loser(field, 2);
            if (loser) {
                std::cout << "player " + std::to_string(loser) + " lose" << std::endl;
                break;
            }
            std::cout << "enter command: ";
            std::cin >> command;
            try {
                if (command == "newGame"){
                    delete this->field;
                    field = rule->createField(adapter);
                    GameBase::prepareGame(2, "baseDefence");
                } else
                {
                    rule->handle(command, baseHandler, 2, "baseDefence");
                }
            }catch (LogicException& exception) {
                std::cout << exception.what()<< std::endl;
            }
            field->print();
        }
    }
};

template<> class Game<Rule1, 3>: public GameBase<Rule1>
{
    Rule1* rule;
    static Game<Rule1, 3> *game;

    Game<Rule1, 3>(){}
public:

    static Game<Rule1, 3>* getInstance(){
        if (game == nullptr)
            game = new Game<Rule1, 3>;
        return game;
    }

    void createGame() override {
        adapter = new Adapter();
        rule = new Rule1();
        this->field = rule->createField(adapter);
        GameBase::createGame();
    }

    void play(){
        GameBase::prepareGame(3, "baseDefence");
        while (true) {
            loser = rule->loser(field, 3);
            if(loser)
            {
                std::cout << "player " + std::to_string(loser) + " lose" << std::endl;
                break;
            }
            std::cout << "enter command: ";
            std::cin >> command;
            try {
                if (command == "newGame"){
                    delete this->field;
                    field = rule->createField(adapter);
                    GameBase::prepareGame(3, "baseDefence");
                } else
                {
                    rule->handle(command, baseHandler, 3, "baseDefence");
                }

            }catch (LogicException& exception) {
                std::cout << exception.what() << std::endl;
            }
            field->print();
        }
    }

};

template<> class Game<Rule2, 2>: public GameBase<Rule1>
{
    Rule2* rule;
    static Game<Rule2, 2> *game;

    Game<Rule2, 2>(){}

public:

    static Game<Rule2, 2>* getInstance(){
        if (game == nullptr)
            game = new Game<Rule2, 2>;
        return game;
    }

    void createGame() override {
        adapter = new Adapter();
        rule = new Rule2();
        field = rule->createField(adapter);
        GameBase::createGame();
    }

    void play(){
        GameBase::prepareGame(2, "titans");
        while (true) {
            loser = rule->loser(field, 2);
            if (loser) {
                std::cout << "player " + std::to_string(loser) + " lose" << std::endl;
                break;
            }
            std::cout << "enter command: ";
            std::cin >> command;
            try {
                if (command == "newGame"){
                    delete this->field;
                    field = rule->createField(adapter);
                    GameBase::prepareGame(2, "titans");
                } else
                {
                    rule->handle(command, baseHandler, 2, "titans");
                }
            } catch (LogicException& exception) {
                std::cout << exception.what() << std::endl;
            }
            field->print();
        }
    }
};

template<> class Game<Rule2, 3>: public GameBase<Rule1>
{
    Rule2* rule;
    static Game<Rule2, 3> *game;

    Game<Rule2, 3>(){}

public:

    static Game<Rule2, 3>* getInstance(){
        if (game == nullptr)
            game = new Game<Rule2, 3>;
        return game;
    }

    void createGame() override {
        adapter = new Adapter();
        rule = new Rule2();
        field = rule->createField(adapter);
        GameBase::createGame();
    }

    void play(){
        GameBase::prepareGame(3, "titans");
        while (true) {
            loser = rule->loser(field, 3);
            if (loser) {
                std::cout << "player " + std::to_string(loser) + " lose" << std::endl;
                break;
            }
            std::cout << "enter command: ";
            std::cin >> command;
            try {
                if (command == "newGame"){
                    delete field;
                    field = rule->createField(adapter);
                    GameBase::prepareGame(3, "titans");
                } else
                {
                    rule->handle(command, baseHandler, 3, "titans");
                }
            }catch (LogicException& exception) {
                std::cout << exception.what() << std::endl;
            }
            field->print();
        }
    }
};
#endif //OOP_1_GAME_H
