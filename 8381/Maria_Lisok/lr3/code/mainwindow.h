#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "facade.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, Game* game = nullptr);
    ~MainWindow();

private slots:
    void gameInfoButton();

    void addNeutralButton();

    void addUnitButton();

    void addBaseButton();

    void moveUnitButton();

    void attackButton();

    void baseInfoButton();

    void unitInfoButton();

    void neutralInfoButton();

    void landscapeInfoButton();

private:
    Ui::MainWindow *ui;
    Facade *facade;
};
#endif // MAINWINDOW_H
