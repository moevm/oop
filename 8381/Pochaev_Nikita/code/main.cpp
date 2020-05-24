#include <iostream>

#include <QApplication>
#include <QGridLayout>
#include <QWidget>
#include <QLabel>
#include <QScreen>

#include "Tests/examples.h"
#include "Game/UIFacade.h"

int main(int argc, char *argv[])
{
    std::shared_ptr<UIFacade> game = std::make_shared<UIFacade>(argc, argv);
    game->start();

    return 0;
}
