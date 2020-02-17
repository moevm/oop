#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QMessageBox>
#include <QGraphicsItem>
#include <QTextItem>
#include "Cell.h"
#include "objects/Archer.h"
#include "objects/Centaur.h"
#include "objects/SpearMan.h"
#include "objects/SwordsMan.h"
#include "objects/Wizard.h"
#include "objects/Panzer.h"

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
    void on_create_cell_clicked();

    void on_add_unit_clicked();

    void on_move_unit_clicked();

private:
    void update();
    Cell *cell = nullptr;
    QGraphicsScene *scene;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
