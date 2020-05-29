#include "game/game.h"

class Test {
public:
    static void test1() {
        Game* game = new Game;
        game->createField(5,5);
        game->addBase(2,2);
        game->addBase(3,3);
        game->printField();
        game->addUnit(0,0,'S',1);
        game->printField();
        game->addUnit(0,1,'E',2);
        game->printField();
        game->moveUnit(0,0,0,1);
        game->printField();
    }

    static void test2() {
        Game* game = new Game;
        game->createField(6,4);
        game->addBase(2,2);
        game->addBase(3,3);
        game->addUnit(0,0,'F',1);
        game->addNeutral(1,1,'c');
        game->printField();
        game->moveUnit(0,0,1,1);
        game->printField();
    }

    static void test3() {
        Game* game = new Game;
        game->createField(5,5);
        game->addBase(4,4);
        game->addUnit(0,0,'S',1);
        game->addUnit(0,1,'F',1);
        game->addUnit(0,2,'E',1);
        game->addUnit(1,0,'S',1);
        game->addUnit(1,1,'E',1);
        game->printField();
        game->addUnit(1,2,'S',1);
        game->printField();
    }

};

int main() {
    Test::test3();

}