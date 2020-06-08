#ifndef BATTLEFORHONOUR_HILLKING_H
#define BATTLEFORHONOUR_HILLKING_H


#include "PlayerState.h"
#include "GameRule.h"
#include "../Game/GameState.h"

class HillKing: public GameRule {

private:
    PlayerState* nowState;
public:

    HillKing():
            GameRule( 15, 15),
            nowState(new FirstPlayer){}
    bool isOver(GameState &gameState) override {
        if(!gameState.getField().getCell(7, 7)->isEmpty() && gameState.getField().getCell(7, 7)->getObject()->getType() != ObjectType::BASE){
            Log::log << "Game over" << Log::logend;
            std::cout << "User " << gameState.getNowPlayerIndex() << " won!";
            return true;
        }
        else
            return false;
    }

    int nextUser(GameState &gameState) override {
        int currUserPos = (gameState.getNowPlayerIndex() + nowState->getNextPlayerRecr()) % gameState.getBases().size();
        auto nextState = nowState->getNextPlayerState();
        delete nowState;
        nowState = nextState;
        if (nowState == nullptr)
            nowState = new FirstPlayer;
        return currUserPos;
    }

};

#endif //BATTLEFORHONOUR_HILLKING_H
