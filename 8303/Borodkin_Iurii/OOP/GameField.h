#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include "Field.h"
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QMouseEvent>
#include <vector>
#include <unordered_map>
#include "gamecell.h"
#include "Landscapes/Proxy/LavaProxy.h"
#include "Objects/Observer/Observer.h"
#include "Neuturals/Packs.h"
#include "Neuturals/Strategy/Strategy.h"
#include "Logger/Logger.h"
#include <Objects/Mediator/DamageMediator.h>

class State;

class GameField : public Field
{
    std::vector <std::vector <GameCell>> gameField;
    std::unordered_map <Object*, std::vector<Object**>> clones;
    unsigned countBase = 0;

public:

    GameField();

    GameField(int, int, int, int);

    void addUnit(Unit*, const Coordinates&);

    void addBase(Base*, const Coordinates&);

    void delObject(const Coordinates&);

    bool move(const Coordinates&, const Coordinates&);

    bool attack(const Coordinates&, const Coordinates&);

    bool canMove(size_t, size_t) const;

    bool canPlaceBuild(size_t, size_t) const;

    GameCell& at(std::pair<size_t, size_t>);

    const GameCell& at(std::pair<size_t, size_t>) const;

    std::vector <Object**> getClones(Coordinates);

    struct Intermediate
    {
        Intermediate(std::vector<GameCell>&);
        GameCell& operator[] (size_t);
        const GameCell& operator[] (size_t) const;
    private:
        std::vector<GameCell> &vec;
    };

    Intermediate operator[](size_t);

    State* state;

    unsigned bases();

    unsigned countPlayers = 0;

};

#endif // GAMEFIELD_H
