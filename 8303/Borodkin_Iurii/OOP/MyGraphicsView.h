#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QWidget>
#include <QGraphicsView>
#include <QPushButton>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QMouseEvent>
#include <QTextBrowser>
#include <vector>
#include "GameField.h"
#include "Logger/LoggerFile.h"
#include "Logger/LoggerEmpty.h"
#include "Logger/LoggerTerminal.h"
#include "Command/Invoker.h"
#include "Game.h"
#include "Memento/Memento.h"
#include "Settings.h"
#include "Rules/States.h"
#include "CreateFieldWindow.h"

struct PressedCell
{
    std::pair <size_t, size_t> coords;
    bool pressedBase = false;
    bool pressedUnit = false;
    std::vector <GameCell*> modCells;
};

class MyGraphicsView : public QGraphicsView
{

    Q_OBJECT

public:
    explicit MyGraphicsView(GameField&, LoggerProxy*, QTextBrowser* = nullptr, QPushButton *add_unit = nullptr, QWidget* = nullptr);

    void update();

    void mousePressEvent(QMouseEvent*) override;

    Invoker inv;

    bool onUndoClicked = false;

    std::pair<size_t, size_t> getCoordsToAddUnit();

    Memento saveState();

    bool win();

    Game <Rule1, Players2>* game1 = nullptr;
    Game <Rule1, Players3>* game2 = nullptr;
    Game <Rule2, Players2>* game3 = nullptr;
    Game <Rule2, Players3>* game4 = nullptr;

private:

    bool _win = false;

    GameField &gameField;

    LoggerProxy* log;

    QGraphicsScene *scene;

    QGraphicsItemGroup *group;

    QTextBrowser *charsObj;

    QPushButton *add_unit;

    QString strChars;

    PressedCell oldCell;

    std::pair <size_t, size_t> coordsToAddUnit;

    void pressedOnUnit(size_t, size_t);

    void pressedOnBase(size_t, size_t);

    void unitControl(size_t, size_t);

    void baseControl(size_t, size_t);

    void deleteItemsFromGroup();
};

#endif // MYGRAPHICSVIEW_H
