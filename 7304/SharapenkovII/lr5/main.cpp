#include <iostream>
#include <string>
#include <Ultralight/Ultralight.h>
#include <AppCore/AppCore.h>
#include "runtime/Game.h"
#include "field/Field.h"
#include "player/Player.h"

using namespace std;
using namespace ultralight;

int main() {

    shared_ptr<Player> p1 = make_shared<Player>("Player 1", "#000000");
    shared_ptr<Player> p2 = make_shared<Player>("Player 2", "#555555");

    Game &game = Game::getGame();

    game.addPlayer(p1);
    game.addPlayer(p2);

    game.createField(25);

    unsigned size = game.getField().getSize();
    unsigned cord = size / 2;

    game.createUnit(Coord(cord,0), "Archer", p1);
    game.createUnit(Coord(cord + 1,0), "Tank", p1);
    game.createUnit(Coord(cord + 2,0), "Knight", p1);
    game.createUnit(Coord(cord + 3,0), "King", p1);
    game.createUnit(Coord(cord + 4,0), "Priest", p1);
    game.createUnit(Coord(cord + 5,0), "Killer", p1);

    game.createUnit(Coord(cord,size - 1), "Archer", p2);
    game.createUnit(Coord(cord - 1,size - 1), "Tank", p2);
    game.createUnit(Coord(cord - 2,size - 1), "Knight", p2);
    game.createUnit(Coord(cord - 3,size - 1), "King", p2);
    game.createUnit(Coord(cord - 4,size - 1), "Priest", p2);
    game.createUnit(Coord(cord - 5,size - 1), "Killer", p2);

    game.createImp(Coord(0, 5), "River");
    game.createImp(Coord(5, 5), "Mountains");
    game.createImp(Coord(15, 5), "Forest");
    game.createImp(Coord(15, 15), "Swamp");
    game.createImp(Coord(19, 19), "Rain");
    game.createImp(Coord(2, 18), "Snow");
    game.createImp(Coord(1, 10), "Fog");

    game.run();

    return 0;
}