#ifndef BATTLEFORHONOUR_MIDGAME_H
#define BATTLEFORHONOUR_MIDGAME_H


#include "GameRule.h"
#include "PlayerState.h"

class MidGame: public GameRule {

private:

    PlayerState* nowState;

public:

    MidGame():
        GameRule(10, 10),
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


#endif //BATTLEFORHONOUR_MIDGAME_H
