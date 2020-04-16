//
// Created by shenk on 18.03.2020.
//

#ifndef UNTITLED13_GAMEFACADE_H
#define UNTITLED13_GAMEFACADE_H

#include <sstream>
#include "GameInfo.h"
#include "UI/MainCommandInterpreter.h"

template<typename Rule, int playersCount>
class GameFacade: public GameInfo {

private:

    MainCommandInterpreter interpreter;
    GameFacade(int fieldWidth, int fieldHeight): GameInfo(playersCount, fieldWidth, fieldWidth, new Rule){}
    Rule rule;

public:

    static GameFacade& instance(){
        Rule rule;
        static GameFacade singleInstance(rule.fieldWidth, rule.fieldHeight);
        return singleInstance;
    }

    void nextTurn(){

        std::string commandString;
        std::getline(std::cin, commandString);

        CommandPtr command = interpreter.handle(commandString);
        command->execute(*this);
        history.push_back(command->getMemento());

        nextUser();

    }

    friend std::ostream &operator<<(std::ostream &stream, const GameFacade &game){

        stream << "Now player: " << game.nowPlayerIndex << std::endl;
        stream << game.gameField << std::endl;
        return stream;

    }

    bool isOver(){

        return rule.isOver(*this);

    }

};


#endif //UNTITLED13_GAMEFACADE_H
