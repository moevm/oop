#ifndef LAB2_OOP_GAMEINFO_H
#define LAB2_OOP_GAMEINFO_H

#include "../GameField.h"
#include "Memento/RequestMemento.h"
#include "Rules/GamingRule.h"
#include "../Exceptions/DoubleBasePlacingException.h"

class GameInfo {
 protected:
  GameField gameField;
  std::vector<Base *> userBases;
  int currentPlayerIndex;
  std::vector<RequestMemento *> historicalData;
  GamingRule *gamingRule;

 public:
  GameInfo(int playersCount, int fieldWidth, int fieldHeight, GamingRule *rule) :
      gameField(fieldHeight, fieldWidth),
      userBases(playersCount, nullptr),
      currentPlayerIndex(0),
      gamingRule(rule)
  {}

  Base *getCurrentPlayerBase() {
    return userBases[currentPlayerIndex];
  }

  bool setCurrentPlayerBase(Base *base, Point &basePosition) {
    if (userBases[currentPlayerIndex]) {
      throw DoubleBasePlacingException(currentPlayerIndex);
    } else {
      if (gameField.getCell(basePosition)->isEmpty())
        userBases[currentPlayerIndex] = base;
    }

    return true;
  }

  int getCurrentPlayerIndex() {
    return currentPlayerIndex;
  }

  void createNewGame() {
    unsigned long playersCount = userBases.size();

    gameField.reset();
    userBases.clear();
    historicalData.clear();
    userBases.resize(playersCount, nullptr);
  }

  void addToHistoricalData(RequestMemento *memento) {
    historicalData.push_back(memento);
  }

  void nextUser() {
    currentPlayerIndex = gamingRule->nextUser(*this);
  }

  std::vector<RequestMemento*> getHistoricalData() {
    return historicalData;
  }

  GameField &getField() {
    return gameField;
  }

  const std::vector<Base*> &getBases(){
    return userBases;
  }
};

#endif //LAB2_OOP_GAMEINFO_H
