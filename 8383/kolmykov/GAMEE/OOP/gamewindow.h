#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include "Demo.h"
#include "Field.h"
#include <QPainter>
#include "twoplayersgame.h"
#include<QBoxLayout>
#include <QPushButton>
#include <QSpacerItem>
#include "paintwidget.h"
#include <QLabel>
#include <QComboBox>
#include <QSpinBox>
#include <QMessageBox>
#include "gamemode.h"
#include "Loader.h"
#include "SingleGame.h"


class GameWindow : public QWidget
{
    Q_OBJECT
public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();
    void setMode(GameMode mode);

private:
    Game<TwoPlayersRule>* game;
    Game<SingleGameRule>* soloGame;
    GameMode mode;

    QHBoxLayout* hLayout;
    QVBoxLayout* vLayout;
    QPushButton* buttonCreate;
    PaintWidget* paintWidget;
    QHBoxLayout* towerLineLayout;
    QHBoxLayout* unitLineLayout;
    QHBoxLayout* unitTypeLayout;
    QLabel* towerLabel;
    QLabel* unitLabel;
    QLabel* typeLabel;
    QSpinBox* towerBox;
    QSpinBox* unitBox;
    QComboBox* typeBox;
    QPushButton* endStepButton;
    QLabel* stateLabel;
    QHBoxLayout* topLaypout;
    QPushButton* buttonNewGame;
    QPushButton* buttonSaveGame;

protected:
   // void paintEvent(QPaintEvent *event);

public slots:
   // void paintItPlease();
    void startNewGame();
    void loadGame();
    void create();
    void endStep();
    void gameEnd();
    void setStepLabel(Kind kind);
    void saveGame();
};

#endif // GAMEWINDOW_H
