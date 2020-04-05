#include <iostream>
#include "Field/Object/ObjectFabric.h"
#include "Field/GameField.h"
#include "Field/Object/Base.h"
#include "Field/Facade.h"

int main()
{
    auto *game = new Facade();
    game->createGame();
    game->playGame();
}
