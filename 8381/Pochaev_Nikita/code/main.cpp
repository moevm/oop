#include <iostream>

#include <QApplication>
#include <QGridLayout>
#include <QWidget>
#include <QLabel>
#include <QScreen>

#include "Tests/examples.h"
#include "Game/game.h"

int main(int argc, char *argv[])
{
    // fieldBasedTest();
    // ObserverDeathTest();
    // landscapeTest();
    unitInteractionTest();

    Game *game = new Game(argc, argv);
    game->start();

    return 0;
}
