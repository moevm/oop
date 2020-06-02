#ifndef LAB2_OOP_TINYGAME_H
#define LAB2_OOP_TINYGAME_H

#include "GamingRule.h"
#include "PlayerState.h"

class TinyGame: public GamingRule {
 private:
  PlayerState* currentState;

 public:
  TinyGame(): GamingRule(3, 3), currentState(new FirstPlayer){}

  bool isGameOver(GameInfo &gameInfo) override {
    int liveCount = gameInfo.getBases().size();
    for (auto base: gameInfo.getBases()){
      if (base && base->getBaseHealth() <= 0){
        liveCount--;
      }
    }

    return liveCount <= 1;
  }

  int nextUser(GameInfo &gameInfo) override {
    int currentPlayerIndex = gameInfo.getCurrentPlayerIndex()+currentState->getNextPlayerDelta();
    currentPlayerIndex %= gameInfo.getBases().size();
    auto nextState = currentState->getNextPlayerState();
    delete currentState;
    currentState = nextState;
    if (currentState == nullptr)
      currentState = new FirstPlayer;
    return currentPlayerIndex;
  }
};

#endif //LAB2_OOP_TINYGAME_H
