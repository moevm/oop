#include "game/game.h"
#include "userInterface/userInterface.h"

class Test {
public:
    static void test1() {
        Game* game = new Game;
        game->createField(10,10);
        game->addBase(9,9);
        game->addUnit(0,0,'E',1);
        UserInterface userInterfase(game);
        userInterfase.run();
    }
    static  void test2() {
        Game* game = new Game;
        game->createField(5,5);
        game->addBase(2,3);
        game->addBase(2,2);
        game->addUnit(0,0,'S',1);
        game->addUnit(0,1,'F',2);
        UserInterface userInterfase(game);
        userInterfase.run();
    }
    static void test3() {
        Game* game = new Game;
        game->createField(7,7);
        game->addBase(0,0);
        game->addBase(6,0);
        game->addBase(0,6);
        game->addUnit(0,1,'S',1);
        game->addUnit(1,0,'F',1);
        game->addUnit(6,1,'F',2);
        game->addUnit(1,6,'F',3);
        UserInterface userInterfase(game);
        userInterfase.run();

    }

};

int main() {
    Test::test1();

}