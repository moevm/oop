#ifndef GAME_H
#define GAME_H

#include <QApplication>
#include <QScreen>

#include "GUI/mainwindow.h"

class Game : QObject
{
    Q_OBJECT

public:
    Game(int argc, char *argv[]);
    ~Game() = default;

    void start();

private:
    QApplication *application;
    // GUI
    MainWindow *window;

    void guiSetup();
    void startGameWindow();
};

#endif // GAME_H
