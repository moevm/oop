#ifndef BATTLEFORHONOUR_GAMESTATE_H
#define BATTLEFORHONOUR_GAMESTATE_H


#include "../User/Commands/CommandSnapshot.h"
#include "../GameField/GameField.h"
#include "../Exceptions/StackExceptions.h"
#include "../GameSettings/GameRule.h"

class GameState {

protected:

    GameField gameField;
    std::vector<Base*> userBases;
    std::vector<CommandSnapshot*> gameActions;
    int currentUser;
    GameRule *rule;

public:

    GameState(int playersCount, int fieldWidth, int fieldHeight, GameRule *rule):
            gameField(fieldHeight, fieldWidth),
            userBases(playersCount, nullptr),
            currentUser(0),
            rule(rule)
    {}

    Base *getNowPlayerBase(){
        return userBases[currentUser];
    }
    bool setNowPlayerBase(Base *base){
        if (userBases[currentUser]){
            throw DoubleBasePlacingExc(currentUser);
        } else{
            userBases[currentUser] = base;
            return true;
        }
    }

    [[nodiscard]] int getNowPlayerIndex() const{
        return currentUser;
    }

    void newGame(){
        int playersCount = userBases.size();
        gameField.reset();
        userBases.clear();
        gameActions.clear();
        userBases.resize(playersCount, nullptr);
    }

    void addAction(CommandSnapshot *snapshot){
        gameActions.push_back(snapshot);
    }

    void nextUser(){
        currentUser = rule->nextUser(*this);
    }

    std::vector<CommandSnapshot*> getActions(){
        return gameActions;
    }

    GameField &getField(){
        return gameField;
    }

    const std::vector<Base*> &getBases(){
        return userBases;
    }

};


#endif //BATTLEFORHONOUR_GAMESTATE_H
