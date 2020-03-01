#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include "gamefield.h"
#include "iterator.h"
#include "base.h"
#include "NeutralObject/poison.h"
#include "NeutralObject/armor.h"
#include "NeutralObject/weapon.h"
#include "NeutralObject/medicine.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
