#ifndef LAB2_OOP_HUGEGAME_H
#define LAB2_OOP_HUGEGAME_H

#include "GamingRule.h"
#include "PlayerState.h"

class BigGame : public GamingRule {
 private:
  PlayerState *currentState;

 public:
  BigGame() : GamingRule(10, 10), currentState(new FirstPlayer) {}

  bool isGameOver(GameInfo &gameInfo) override {
    return false;
  }

  int nextUser(GameInfo &gameInfo) override {
    int currentPlayerIndex = gameInfo.getCurrentPlayerIndex() + currentState->getNextPlayerDelta();
    currentPlayerIndex %= gameInfo.getBases().size();
    auto nextState = currentState->getNextPlayerState();
    delete currentState;
    currentState = nextState;
    if (currentState == nullptr)
      currentState = new FirstPlayer;
    return currentPlayerIndex;
  }
};

#endif //LAB2_OOP_HUGEGAME_H
