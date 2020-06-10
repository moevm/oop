#include <QCoreApplication>
#include <QMediaPlayer>
#include <QDir>
#include <QUrl>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <conio.h>
#include "game.h"

using namespace std;

#define UP_ARROW 72
#define LEFT_ARROW 75
#define DOWN_ARROW 80
#define RIGHT_ARROW 77

Game<Rule1>* Game<Rule1>::game = nullptr;
Game<Rule2>* Game<Rule2>::game = nullptr;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    cout << "Choose the game mode(1 - classic, 2 - sheihmod): ";
    int mode;
    cin >> mode;
    cout << endl;
    if (mode == 1){
        auto *game = Game<Rule1>::getInst();
        game->createGame();
        game->play();
    }
    if (mode == 2){
        auto *game = Game<Rule2>::getInst();
        game->createGame();
        game->play();
    }
    if (mode != 1 && mode != 2){
        cout << "You are too dumm for this game, without negative.\n";
    }
    cout << "\nGame Over!";
    return a.exec();
}
