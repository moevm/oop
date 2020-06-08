#ifndef BATTLEFORHONOUR_SMALLGAME_H
#define BATTLEFORHONOUR_SMALLGAME_H


#include "GameRule.h"
#include "PlayerState.h"

class SmallGame: public GameRule {

private:

    PlayerState* nowState;

public:

    SmallGame():
        GameRule( 7, 7),
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

        int nowPlayerIndex = (gameState.getNowPlayerIndex() + nowState->getNextPlayerRecr()) % gameState.getBases().size();
        auto nextState = nowState->getNextPlayerState();
        delete nowState;
        nowState = nextState;
        if (nowState == nullptr)
            nowState = new FirstPlayer;
        return nowPlayerIndex;
    }
};

#endif //BATTLEFORHONOUR_SMALLGAME_H
