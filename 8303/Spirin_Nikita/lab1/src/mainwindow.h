#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>


#include "gamefield.h"
#include "factoryofshooters.h"
#include "factoryofinfantry.h"
#include "factoryofhorsemen.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

void example1();
void example2();
void example3();

#endif // MAINWINDOW_H

