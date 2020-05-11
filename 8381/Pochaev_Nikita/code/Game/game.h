#ifndef GAME_H
#define GAME_H

#include <cstddef>
#include <vector>
#include <map>
#include <utility>

#include <QString>

#include "AuxiliaryFunctionality/TextColoring.h"
#include "GameField/GameFieldProxy.h"
#include "GameField/Coords.h"
#include "IGame.h"

// Base creation
#include "Bases/BaseMaster.h"
#include "Bases/HumanBase.h"
#include "Bases/HumanBaseBuilder.h"
#include "Bases/HellBaseBuilder.h"
#include "Bases/HellBase.h"

class FacadeMediator;

struct BaseInf
{
    BaseInf() = default;
    BaseInf(std::shared_ptr<GameBase> base_, size_t xCoord_, size_t yCoord_) :
        base(std::move(base_)), xCoord(xCoord_), yCoord(yCoord_) { };

    std::shared_ptr<GameBase> base;
    size_t xCoord{}, yCoord{};
};

// TODO: вектор игроков, кнопка передачи хода с вызовом соответствующих параметров

class Game : public IGame
{
public:
    Game(size_t fieldHeight, size_t fieldWidth, bool fill = false);
    Game(size_t fieldHeight, size_t fieldWidth, size_t playersCount_, bool fill = false);

    // Getters
    std::shared_ptr<GameFieldProxy> getField() const;
    std::map<QString, BaseInf> getBases() const;
    std::shared_ptr<GameBase> getBaseByNumber(size_t number);
    bool getBaseCoordsByName(QString sourceBaseName, Coords &coords);

    // Information getters
    std::string getGameInf();
    std::string getBaseInfo(size_t x, size_t y);
    std::string getUnitInfo(size_t x, size_t y);
    std::string getItemInfo(size_t x, size_t y);
    std::string getLandInfo(size_t x, size_t y);

    size_t getPlayersCount();

    // Setters
    void createBase(eBaseType type, size_t xCoord, size_t yCoord, QString name) override;
    void createUnit(eUnitsType, size_t xCoord, size_t yCoord) override;
    void moveUnit(size_t xSource, size_t ySource, size_t xDest, size_t yDist) override;
    void unitAttack(size_t xSource, size_t ySource, size_t xDest, size_t yDist) override;

    // Memento restore
    std::shared_ptr<GameParametersCaretaker> createMemento();
    void restoreMemento(std::shared_ptr<GameParametersCaretaker>);

private:
    size_t playersCount{};

    std::shared_ptr<GameFieldProxy> field;
    std::map<QString, BaseInf> bases;
    BaseMaster master;
    HellBaseBuilder hellBaseBuilder;
    HumanBaseBuilder humanBaseBuilder;

    std::shared_ptr<FacadeMediator> facadeMediator;
};

#endif // GAME_H
