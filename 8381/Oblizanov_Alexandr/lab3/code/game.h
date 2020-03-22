#ifndef GAME_H
#define GAME_H
#include "attackmediator.h"

class Game : public IGame
{
public:
    Game(unsigned x, unsigned y, unsigned limit, LandType basicLand);
    void createBase(std::string name, unsigned limit, unsigned x, unsigned y);
    Field *getField() const;
    std::vector<Base *> getBases() const;
    std::vector<IUnit *> getUnits() const;
    Base *getBaseByNumber(unsigned number);
    void addUnit(IUnit *unit, Base *base);
    void deleteUnit(IUnit *unit, Base *base);
    void createNeutral(unsigned x, unsigned y, NeutralType type);
private:
    Field *field;
    AttackMediator *units;
    std::vector<Base *> bases;
    IGameMediator *baseMediator;
};

class GameMediator : public IGameMediator
{
public:
    GameMediator(Game *game, Base *base)
        :game(game), base(base) {
        base->setGameMediator(this);
    }
    void Notify(IUnit *unit, bool add) {
        if (add)
            game->addUnit(unit, base);
        else
            game->deleteUnit(unit, base);
    }
private:
    Game *game;
    Base *base;
};



#endif // GAME_H
