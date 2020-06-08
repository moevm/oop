//
// Created by therealyou on 01.06.2020.
//

#ifndef LAB1_GAME_H
#define LAB1_GAME_H

#include "Facade.h"
#include "Rules.h"

template<typename Rule>
class GameBase {
protected:
    GameField *gameField;
    Adapter *adapter;
    int loser;
    std::string command;

    BaseHandler *baseHandler;
    BaseHandler *setBaseHandler;
    BaseHandler *setUnitHandler;
    BaseHandler *moveUnitRightHandler;
    BaseHandler *moveUnitLeftHandler;
    BaseHandler *moveUnitUpHandler;
    BaseHandler *moveUnitDownHandler;
    BaseHandler *attackUnitHandler;
    BaseHandler *showStatusHandler;
    BaseHandler *helpHandler;
    BaseHandler *adapterHandler;
    BaseHandler *turnOnOffLog;
    BaseHandler *saveHandler;
    BaseHandler *loadHandler;
    BaseHandler *setTitanHandler;

    virtual void createGame() {
        baseHandler = new BaseHandler(gameField);
        setBaseHandler = new SetBaseHandler(gameField);
        setUnitHandler = new SetUnitHandler(gameField);
        moveUnitLeftHandler = new MoveUnitLeftHandler(gameField);
        moveUnitDownHandler = new MoveUnitDownHandler(gameField);
        moveUnitUpHandler = new MoveUnitUpHandler(gameField);
        moveUnitRightHandler = new MoveUnitRightHandler(gameField);
        attackUnitHandler = new AttackUnitHandler(gameField);
        showStatusHandler = new ShowStatusHandler(gameField);
        helpHandler = new HelpHandler(gameField);
        adapterHandler = new SwitchLogHandler(adapter);
        turnOnOffLog = new TurnOnOffLog(adapter);
        saveHandler = new SaveHandler(adapter, gameField);
        loadHandler = new LoadHandler(adapter, gameField);
        setTitanHandler = new SetTitanHandler(adapter, gameField);

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

    void prepareGame(int playersNumber, std::string gameMode) {
        std::string mode = "prepare";
        try {
            std::cout << "Load game or new game?(load/new): ";
            std::cin >> command;

            if (command != "new" && command != "load")
                throw LogicException("incorrect game choice", command);
            if (command == "load") {
                baseHandler->handle(command, playersNumber, mode);
            } else {
                if (gameMode == "baseDefence")
                    createBase(playersNumber);
                else
                    createTitans(playersNumber);
            }
        } catch (LogicException &exception) {
            std::cout << exception.what() << std::endl;
            prepareGame(playersNumber, gameMode);
        } catch (TypeException &exception) {
            std::cout << exception.what() << std::endl;
            prepareGame(playersNumber, gameMode);
        } catch (CheckException &exception) {
            std::cout << exception.what() << std::endl;
            prepareGame(playersNumber, gameMode);
        }
    }

    void createBase(int countBase) {
        gameField->printFieldLandscape();
        gameField->printFieldNeutralObject();
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

    void createTitans(int countBase) {
        try {
            gameField->printField();
            gameField->printFieldLandscape();
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
        } catch (LogicException &exception) {
            std::cout << exception.what() << std::endl;
            createTitans(countBase);
        } catch (TypeException &exception) {
            std::cout << exception.what() << std::endl;
            createTitans(countBase);
        } catch (CheckException &exception) {
            std::cout << exception.what() << std::endl;
            createTitans(countBase);
        }
    }

public:
};

template<typename Rule, int>
class Game : public GameBase<Rule> {
};

template<>
class Game<Rule1, 2> : public GameBase<Rule1> {
    Rule1 *rule;
    static Game<Rule1, 2> *game;

    Game<Rule1, 2>() {}

public:

    static Game<Rule1, 2> *getInstance() {
        if (game == nullptr)
            game = new Game<Rule1, 2>;
        return game;
    }

    void createGame() override {
        adapter = new Adapter();
        rule = new Rule1();
        gameField = rule->createField(adapter);
        GameBase::createGame();
    }

    void play() {
        GameBase::prepareGame(2, "baseDefence");
        while (true) {
            loser = rule->loser(gameField, 2);
            if (loser) {
                std::cout << "player " + std::to_string(loser) + " lose" << std::endl;
                break;
            }
            std::cout << "enter command: ";
            std::cin >> command;
            try {
                if (command == "newGame") {
                    delete this->gameField;
                    gameField = rule->createField(adapter);
                    GameBase::prepareGame(2, "baseDefence");
                } else {
                    rule->handle(command, baseHandler, 2, "baseDefence");
                }
            } catch (LogicException &exception) {
                std::cout << exception.what() << std::endl;
            }
            gameField->printField();
        }
    }
};

template<>
class Game<Rule1, 3> : public GameBase<Rule1> {
    Rule1 *rule;
    static Game<Rule1, 3> *game;

    Game<Rule1, 3>() {}

public:

    static Game<Rule1, 3> *getInstance() {
        if (game == nullptr)
            game = new Game<Rule1, 3>;
        return game;
    }

    void createGame() override {
        adapter = new Adapter();
        rule = new Rule1();
        this->gameField = rule->createField(adapter);
        GameBase::createGame();
    }

    void play() {
        GameBase::prepareGame(3, "baseDefence");
        while (true) {
            loser = rule->loser(gameField, 3);
            if (loser) {
                std::cout << "player " + std::to_string(loser) + " lose" << std::endl;
                break;
            }
            std::cout << "enter command: ";
            std::cin >> command;
            if (command == "newGame") {
                delete this->gameField;
                gameField = rule->createField(adapter);
                GameBase::prepareGame(3, "baseDefence");
            }
            rule->handle(command, baseHandler, 3, "baseDefence");
            try {
                if (command == "newGame") {
                    delete this->gameField;
                    gameField = rule->createField(adapter);
                    GameBase::prepareGame(3, "baseDefence");
                } else {
                    rule->handle(command, baseHandler, 3, "baseDefence");
                }

            } catch (LogicException &exception) {
                std::cout << exception.what() << std::endl;
            }
            gameField->printField();
        }
    }

};

template<>
class Game<Rule2, 2> : public GameBase<Rule1> {
    Rule2 *rule;
    static Game<Rule2, 2> *game;

    Game<Rule2, 2>() {}

public:

    static Game<Rule2, 2> *getInstance() {
        if (game == nullptr)
            game = new Game<Rule2, 2>;
        return game;
    }

    void createGame() override {
        adapter = new Adapter();
        rule = new Rule2();
        gameField = rule->createField(adapter);
        GameBase::createGame();
    }

    void play() {
        GameBase::prepareGame(2, "titans");
        while (true) {
            loser = rule->loser(gameField, 2);
            if (loser) {
                std::cout << "player " + std::to_string(loser) + " lose" << std::endl;
                break;
            }
            std::cout << "enter command: ";
            std::cin >> command;
            try {
                if (command == "newGame") {
                    delete this->gameField;
                    gameField = rule->createField(adapter);
                    GameBase::prepareGame(3, "titans");
                } else {
                    rule->handle(command, baseHandler, 3, "titans");
                }

            } catch (LogicException &exception) {
                std::cout << exception.what() << std::endl;
            }
            gameField->printField();
        }
    }
};

template<>
class Game<Rule2, 3> : public GameBase<Rule1> {
    Rule2 *rule;
    static Game<Rule2, 3> *game;

    Game<Rule2, 3>() {}

public:

    static Game<Rule2, 3> *getInstance() {
        if (game == nullptr)
            game = new Game<Rule2, 3>;
        return game;
    }

    void createGame() override {
        adapter = new Adapter();
        rule = new Rule2();
        gameField = rule->createField(adapter);
        GameBase::createGame();
    }

    void play() {
        GameBase::prepareGame(3, "titans");
        while (true) {
            loser = rule->loser(gameField, 3);
            if (loser) {
                std::cout << "player " + std::to_string(loser) + " lose" << std::endl;
                break;
            }
            std::cout << "enter command: ";
            std::cin >> command;
            try {
                if (command == "newGame") {
                    delete gameField;
                    gameField = rule->createField(adapter);
                    GameBase::prepareGame(3, "titans");
                } else {
                    rule->handle(command, baseHandler, 3, "titans");
                }
            } catch (LogicException &exception) {
                std::cout << exception.what() << std::endl;
            }
            gameField->printField();
        }
    }
};

#endif //LAB1_GAME_H
