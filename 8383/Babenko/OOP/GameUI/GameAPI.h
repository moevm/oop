#ifndef LAB2_OOP_GAMEAPI_H
#define LAB2_OOP_GAMEAPI_H

//Facade

#include <sstream>
#include "GameInfo.h"
#include "MainRequestInterpreter.h"
#include "../Exceptions/DoublePlacingOnFieldException.h"
#include "../Exceptions/GameFieldOutOfRangeException.h"
#include "../Exceptions/ImpossibleMoveException.h"

template<typename Rule, int playersCount>
class GameAPI : public GameInfo {
 private:
  MainRequestInterpreter interpreter;
  GameAPI(int fieldWidth, int fieldHeight) : GameInfo(playersCount, fieldWidth, fieldWidth, new Rule) {}
  Rule gamingRule;

 public:
  static GameAPI &instance() {
    Rule rule;
    static GameAPI singleInstance(rule.fieldWidth, rule.fieldHeight);
    return singleInstance;
  }

  void nextTurn() {
    std::string requestString;
    std::getline(std::cin, requestString);

    RequestPtr request = interpreter.handle(requestString);
    try {
      request->execute(*this);
    } catch (DoubleBasePlacingException &exception) {
      game::log << "[Game] Player " << exception.playerIndex << " trying to place base second time." << game::logend;
    } catch (DoublePlacingOnFieldException &exception) {
      game::log << "[Game] This cell is busy by other object." << game::logend;
    } catch (GameFieldOutOfRangeException &exception) {
      game::log << "[Game] Out of range. Cell " << exception.x << " " << exception.y << " does not exist." << game::logend;
    } catch (ImpossibleMoveException &exception) {
      game::log << "[Game] Can't move object to this cell." << game::logend;
    } catch (InvalidFileLoaddingException &exception) {
      game::log << "[Game] Wrong file." << game::logend;
    } catch (...) {
      game::log << "[Game] Undefined error." << game::logend;
    }
    historicalData.push_back(request->getMemento());

    nextUser();
  }

  friend std::ostream &operator<<(std::ostream &stream, const GameAPI &game) {
    stream << "[Game] Current player: " << game.currentPlayerIndex << std::endl;
    stream << game.gameField << std::endl;
    return stream;
  }

  bool isGameOver() {
    return gamingRule.isGameOver(*this);
  }
};

#endif //LAB2_OOP_GAMEAPI_H
