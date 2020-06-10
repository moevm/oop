#include "MyGraphicsView.h"
#include <QDebug>

MyGraphicsView::MyGraphicsView(GameField& field, LoggerProxy* l, QTextBrowser* charsObj, QPushButton* add_unit, QWidget* parent) :
                               QGraphicsView(parent), gameField(field), log(l), charsObj(charsObj), add_unit(add_unit)
{
    if (field.empty()) { return; }

    scene = new QGraphicsScene();
    inv.setField(&field);
    this->setScene(scene);
    update();
}

std::pair<size_t, size_t> MyGraphicsView::getCoordsToAddUnit()
{
    return coordsToAddUnit;
}

void MyGraphicsView::mousePressEvent(QMouseEvent *e)
{
    if (gameField.empty()) { return; }

    if (onUndoClicked)
    {
        onUndoClicked = false;
        for (auto i : oldCell.modCells)
            i->brush = i->landscape->brush();

        oldCell.pressedBase = false;
        oldCell.pressedUnit = false;
    }

    size_t i, j;
    i = static_cast <size_t> (e->pos().y() / (728.0 / gameField.height()));
    j = static_cast <size_t> (e->pos().x() / (728.0 / gameField.width()));


    //First click processing:
    //-----------------------
    if (!(oldCell.pressedBase || oldCell.pressedUnit))
    {
        if (isUnit(gameField[i][j].obj))
        {
            pressedOnUnit(i, j);
            add_unit->hide();
        }

        if (isBase(gameField[i][j].obj))
        {
            pressedOnBase(i, j);
            coordsToAddUnit = {i, j};
            add_unit->show();
        }

        return;
    }

    //Second click processing:
    //------------------------
    for (auto i : oldCell.modCells)
        i->brush = i->landscape->brush();

    oldCell.modCells.clear();

    if (oldCell.pressedUnit)
        unitControl(i, j);

    if (oldCell.pressedBase)
        baseControl(i, j);

    if (game1) {
        gameField.state = game1->getNextState();
    } else if (game2) {
        gameField.state = game2->getNextState();
    } else if (game3) {
        gameField.state = game3->getNextState();
    } else if (game4) {
        gameField.state = game4->getNextState();
    }
}

void MyGraphicsView::pressedOnUnit(size_t i, size_t j)
{
    *log << "User pressed on: " + gameField[i][j].obj->type();
    if (!gameField[i][j].canMove() || !gameField.state->stateObject({i, j})) return;

    size_t y = i;
    size_t x = j;
    int rangeAttack = int(gameField[y][x].obj->range());
    int distance = int(gameField[y][x].obj->travelDistance());

    for (int _i = int(y) - 1; _i >= int(y) - rangeAttack; _i--)
    {
        size_t i = size_t(_i);

        if (_i < 0) continue;
        if (_i >= int(gameField.height())) break;

        auto &cell = gameField[i][j];

        if (cell.obj && !gameField.state->stateObject({i, j})) {
            cell.brush = Qt::red;
            oldCell.modCells.push_back(&cell);
            break;
        }
    }

    for (int _i = int(y) + 1; _i <= int(y) + rangeAttack; _i++)
    {
        size_t i = size_t(_i);

        if (_i < 0) continue;
        if (_i >= int(gameField.height())) break;

        auto &cell = gameField[i][j];

        if (cell.obj && !gameField.state->stateObject({i, j})) {
            cell.brush = Qt::red;
            oldCell.modCells.push_back(&cell);
            break;
        }
    }

    for (int _j = int(x) - 1; _j >= int(x) - rangeAttack; _j--)
    {
        size_t j = size_t(_j);

        if (_j < 0) continue;
        if (_j >= int(gameField.width())) break;

        auto &cell = gameField[i][j];

        if (cell.obj && !gameField.state->stateObject({i, j})) {
            cell.brush = Qt::red;
            oldCell.modCells.push_back(&cell);
            break;
        }
    }

    for (int _j = int(x) + 1; _j <= int(x) + rangeAttack; _j++)
    {
        size_t j = size_t(_j);

        if (_j < 0) continue;
        if (_j >= int(gameField.width())) break;

        auto &cell = gameField[i][j];


        if (cell.obj && !gameField.state->stateObject({i, j})) {
            cell.brush = Qt::red;
            oldCell.modCells.push_back(&cell);
            break;
        }
    }

    for (int _i = int(y) - 1; _i >= int(y) - distance; _i--)
    {
        size_t i = size_t(_i);

        if (_i < 0) continue;
        if (_i >= int(gameField.height())) break;

        auto &cell = gameField[i][j];

        if (cell.canStandUnit())
            cell.brush = Qt::black;
        else
            break;

        oldCell.modCells.push_back(&cell);
    }

    for (int _i = int(y) + 1; _i <= int(y) + distance; _i++)
    {
        size_t i = size_t(_i);

        if (_i < 0) continue;
        if (_i >= int(gameField.height())) break;

        auto &cell = gameField[i][j];

        if (cell.canStandUnit())
            cell.brush = Qt::black;
        else
            break;

        oldCell.modCells.push_back(&cell);
    }

    for (int _j = int(x) - 1; _j >= int(x) - distance; _j--)
    {
        size_t j = size_t(_j);

        if (_j < 0) continue;
        if (_j >= int(gameField.width())) break;

        auto &cell = gameField[i][j];

        if (cell.canStandUnit())
            cell.brush = Qt::black;
        else
            break;

        oldCell.modCells.push_back(&cell);
    }

    for (int _j = int(x) + 1; _j <= int(x) + distance; _j++)
    {
        size_t j = size_t(_j);

        if (_j < 0) continue;
        if (_j >= int(gameField.width())) break;

        auto &cell = gameField[i][j];

        if (cell.canStandUnit())
            cell.brush = Qt::black;
        else
            break;

        oldCell.modCells.push_back(&cell);
    }

    oldCell.coords = {y, x};
    oldCell.pressedUnit = true;

    strChars.append(QString(gameField[y][x].obj->type().c_str()) + '\n');
    strChars.append("Hp: "     + QString::number(gameField[y][x].obj->health()) + '\n');
    strChars.append("Armor: "  + QString::number(gameField[y][x].obj->armor())  + '\n');
    strChars.append("Damage: " + QString::number(gameField[y][x].obj->damage()) + '\n');
    strChars.append("Mana: "   + QString::number(gameField[y][x].obj->mana())   + '\n');

    update();
}

void MyGraphicsView::pressedOnBase(size_t i, size_t j)
{
    *log << "User pressed on Base";

    if (!gameField.canMove(i, j) || gameField[i][j].obj->empty() || !gameField.state->stateObject({i, j})) return;

    if (i > 0)
    {
        auto &cell = gameField[i-1][j];

        if (cell.canStandUnit())
            cell.brush = Qt::black;

        oldCell.modCells.push_back(&cell);
    }

    if (j > 0)
    {
        auto &cell = gameField[i][j-1];

        if (cell.canStandUnit())
            cell.brush = Qt::black;

        oldCell.modCells.push_back(&cell);
    }

    if (i + 1 < gameField.height())
    {
        auto &cell = gameField[i+1][j];

        if (cell.canStandUnit())
            cell.brush = Qt::black;

        oldCell.modCells.push_back(&cell);
    }

    if (j + 1 < gameField.width())
    {
        auto &cell = gameField[i][j+1];

        if (cell.canStandUnit())
            cell.brush = Qt::black;

        oldCell.modCells.push_back(&cell);
    }

    oldCell.coords = {i, j};
    oldCell.pressedBase = true;

    strChars.append(QString(gameField[i][j].obj->type().c_str()) + '\n');
    strChars.append("Hp: " + QString::number(gameField[i][j].obj->health()) + '\n');
    strChars.append("Units: \n");
    MonitorBase mBase;
    Reflector ref;

    mBase.addObserver(ref);
    mBase.resetBase(*dynamic_cast<Base*>(gameField[i][j].obj), &strChars);

    update();
}

void MyGraphicsView::unitControl(size_t i, size_t j)
{
    oldCell.pressedUnit = false;

    if (!gameField[i][j].obj)
    {
//      gameField.move(oldCell.coords, {int(i), int(j)});
        *log << "Unit move to (" + std::to_string(i) + "; " + std::to_string(j) + ")";
        inv.moveUnit(oldCell.coords, {int(i), int(j)});
    }
    else if (!gameField.state->stateObject({i, j}))
    {
//      gameField.attack(oldCell.coords, {int(i), int(j)});
        *log << "Unit attack: " + gameField[i][j].obj->type();
        inv.attackUnit(oldCell.coords, {int(i), int(j)});
        if (gameField[i][j].obj && gameField[i][j].obj->type() != "Base" && gameField[i][j].obj->health() <= 0)
            inv.deathUnit({int(i), int(j)}, gameField.at(oldCell.coords).obj->damage());
        else if (gameField[i][j].obj && gameField[i][j].obj->type() == "Base" && gameField[i][j].obj->health() <= 0) {
            inv.destroyBase({int(i), int(j)}, gameField.at(oldCell.coords).obj->damage(), gameField.getClones({int(i), int(j)}));
            if (game1) {
                if (game1->endGame())
                    _win = true;
            } else if (game2) {
                if (game2->endGame())
                    _win = true;
            } else if (game3) {
                if (game3->endGame())
                    _win = true;
            } else if (game4) {
                if (game4->endGame())
                    _win = true;
            }
        }

        if (gameField[i][j].obj)
        {
            if (gameField[i][j].obj->type() != "Base")
            {
                strChars.append(QString(gameField[i][j].obj->type().c_str()) + '\n');
                strChars.append("Hp: "     + QString::number(gameField[i][j].obj->health()) + '\n');
                strChars.append("Armor: "  + QString::number(gameField[i][j].obj->armor())  + '\n');
                strChars.append("Damage: " + QString::number(gameField[i][j].obj->damage()) + '\n');
                strChars.append("Mana: "   + QString::number(gameField[i][j].obj->mana())   + '\n');
            } else {
                strChars.append(QString(gameField[i][j].obj->type().c_str()) + '\n');
                strChars.append("Hp: "     + QString::number(gameField[i][j].obj->health()) + '\n');
                strChars.append("Units: \n");
                MonitorBase mBase;
                Reflector ref;

                mBase.addObserver(ref);
                mBase.resetBase(*dynamic_cast<Base*>(gameField[i][j].obj), &strChars);
            }
        }
    }

    update();
}

void MyGraphicsView::baseControl(size_t i, size_t j)
{
    oldCell.pressedBase = false;

    if (gameField[i][j].canStandUnit())
    {
        add_unit->hide();
    }

    if (!gameField[i][j].canStandUnit() && gameField[i][j].obj->type() == "Base")
    {
        oldCell.pressedBase = true;
        add_unit->show();
        for (auto i : oldCell.modCells)
            i->brush = i->landscape->brush();

        oldCell.modCells.clear();

        pressedOnBase(i, j);

        return;

    } else if (!gameField[i][j].canStandUnit() && gameField[i][j].obj->type() != "Base") {

        add_unit->hide();
        for (auto i : oldCell.modCells)
            i->brush = i->landscape->brush();

        oldCell.modCells.clear();

        return;
    }

    if (abs(int(oldCell.coords.first) - int(i)) == 1 && oldCell.coords.second == j)
    {
        *log << "Unit leave Base";
        inv.entryFromBase(gameField.at(oldCell.coords).obj, {int(i), int(j)});
        //gameField.addUnit(gameField.at(oldCell.coords).obj->getUnit(), {int(i), int(j)});
    }
    else if (abs(int(oldCell.coords.second) - int(j)) == 1 && oldCell.coords.first == i)
    {
        *log << "Unit leave Base";
        inv.entryFromBase(gameField.at(oldCell.coords).obj, {int(i), int(j)});
        //gameField.addUnit(gameField.at(oldCell.coords).obj->getUnit(), {int(i), int(j)});
    }

    update();
}

void MyGraphicsView::update()
{
    scene->clear();
    charsObj->clear();

    charsObj->append(strChars);
    strChars.clear();

    if (onUndoClicked)
    {
        onUndoClicked = false;
        for (auto i : oldCell.modCells)
            i->brush = i->landscape->brush();

        oldCell.pressedBase = false;
        oldCell.pressedUnit = false;
    }


    double x1 = 0.0, y1 = 0.0;
    for (size_t i = 0; i < gameField.height(); i++) {
        for (size_t j = 0; j < gameField.width(); j++) {

            if (gameField[i][j].obj) {

                scene->addRect(gameField[i][j].rectf,
                               gameField[i][j].pen,
                               gameField[i][j].brush);

                QGraphicsTextItem* txt = new QGraphicsTextItem(gameField[i][j].obj->type().c_str());
                txt->setX(x1 + 728.0 / gameField.width() / 5);
                txt->setY(y1 + 728.0 / gameField.height() / 5);
                scene->addItem(txt);
                x1 += 728.0 / gameField.width();

            } else if (gameField[i][j].pack) {

                scene->addRect(gameField[i][j].rectf,
                               gameField[i][j].pen,
                               gameField[i][j].brush);

                QGraphicsTextItem* txt = new QGraphicsTextItem(gameField[i][j].pack->type().c_str());
                txt->setX(x1 + 728.0 / gameField.width() / 5);
                txt->setY(y1 + 728.0 / gameField.height() / 5);
                scene->addItem(txt);
                x1 += 728.0 / gameField.width();
            } else {

                scene->addRect(gameField[i][j].rectf,
                               gameField[i][j].pen,
                               gameField[i][j].brush);
                x1 += 728.0 / gameField.width();

            }
        }
        y1 += 728.0 / gameField.height();
        x1 = 0.0;
    }
}

Memento MyGraphicsView::saveState()
{
    return Memento(&gameField);
}

bool MyGraphicsView::win()
{
    return _win;
}
