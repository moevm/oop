#ifndef UIFACADE_H
#define UIFACADE_H

#include <QApplication>
#include <QScreen>

#include "GUI/mainwindow.h"
#include "InformationHeaders/commandPar.h"
#include "game.h"

class UIFacade : QObject
{
    Q_OBJECT

public:
    UIFacade(int argc, char *argv[]);
    ~UIFacade();

    void start();
    void receiveStrAnswer(Request request, std::string answer);

private:
    QApplication *application;
    // GUI
    MainWindow *window;
    // Game
    Game *game;
    void guiSetup();
    void startGameWindow();

public slots:
    void createFieldRequest(size_t fieldSize, size_t playersCount);
    //void addUnitRequest();
};

#endif // UIFACADE_H
