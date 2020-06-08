#ifndef BATTLEFORHONOUR_BIGGAME_H
#define BATTLEFORHONOUR_BIGGAME_H


#include "GameRule.h"
#include "PlayerState.h"

class BigGame: public GameRule {

private:
    PlayerState* nowState;
public:

    BigGame():
        GameRule( 15, 15),
        nowState(new FirstPlayer){}
    bool isOver(GameState &gameState) override {
        int liveCount = gameState.getBases().size();
        for (auto b: gameState.getBases()){
            if (b && b->getHealth() <= 0){
                liveCount--;
            }
        }
        return liveCount <= 1;
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


#endif //BATTLEFORHONOUR_BIGGAME_H
