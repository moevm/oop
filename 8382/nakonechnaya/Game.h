#ifndef OOP_GAME_H
#define OOP_GAME_H
#include "Facade.h"

template <typename Rule>
class Game {
public:
    explicit Game(Rule *rules) : rules(rules) {
        facade = new Facade();
    };
    void startGame() {
        facade->startGame(rules);
        facade->makeAction();}
    ~Game() = default;
private:
    Rule *rules;
    Facade *facade;
};
#endif //OOP_GAME_H
