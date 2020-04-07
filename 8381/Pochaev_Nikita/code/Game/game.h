#ifndef GAME_H
#define GAME_H

#include <cstddef>
#include <vector>
#include <map>

#include "GameField/GameFieldProxy.h"
#include "IGame.h"
#include "IGameMediator.h"

// TODO: вектор игроков, кнопка передачи хода с вызовом соответствующих параметров

class Game : public IGame
{
public:
    Game(size_t fieldHieght, size_t fieldWidth);

    // Getters
    std::shared_ptr<GameFieldProxy> getField() const;
    std::vector<std::shared_ptr<GameBase>> getBases() const;
    std::vector<std::shared_ptr<Unit>> getUnits() const;
    std::shared_ptr<GameBase> getBaseByNumber(size_t nuumber);

    // Setters
    void createBase(Coords coords, BaseType type) override;


private:
    std::unique_ptr<GameFieldProxy> field;
    std::vector<std::unique_ptr<GameBase>> bases;
    std::shared_ptr<IGameMediator> *baseMediator;
};

#endif // GAME_H
