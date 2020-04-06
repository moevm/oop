#include "gamewindow.h"

GameWindow::GameWindow()
{
    setupGameWindow();
}

void GameWindow::closeEvent(QCloseEvent* event)
{
    emit gameWindowClosed();
    event->accept();
}

void GameWindow::setupGameWindow()
{
    // BUTTONS SETUP
    addUnitButton->setText("Add unit");
    addBaseButton->setText("Add base");
    moveUnitButton->setText("Move unit");
    attackUnitButton->setText("Attack unit");

    // SETUP LABELS
    unitTypeLabel->setText("Unit types:");
}
