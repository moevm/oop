#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QMessageBox>
#include <QGraphicsItem>
#include <QTextItem>
#include "CreateFieldWindow.h"
#include "Settings.h"
#include "MyGraphicsView.h"
#include "GameField.h"
#include "Command/Commands.h"
#include "Objects/AbstractFactory/UnitsAbstractFactory.h"
#include "Logger/Logger.h"
#include "Logger/LoggerFile.h"
#include "Logger/LoggerTerminal.h"
#include "Logger/LoggerEmpty.h"
#include "Logger/Adapter/Adapter.h"
#include "Memento/GameSaveLoad.h"
#include "exceptions/doubleplacefield.h"
#include "Game.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_create_field_clicked();

    void on_add_unit_clicked();

    void on_actionSettings_triggered();

    void on_undoAction_triggered();

    void on_actionSave_triggered();

    void on_actionLoad_triggered();

private:
    GameField *field;
    MyGraphicsView *gameField;
    CreateFieldWindow *createFieldWindow;
    Settings *settings;
    LoggerProxy log;
    Ui::MainWindow *ui;
    Game <Rule1, Players2>* game1 = nullptr;
    Game <Rule1, Players3>* game2 = nullptr;
    Game <Rule2, Players2>* game3 = nullptr;
    Game <Rule2, Players3>* game4 = nullptr;
};
#endif // MAINWINDOW_H
