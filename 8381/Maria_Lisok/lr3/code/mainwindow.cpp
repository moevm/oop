#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, Game *game)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    facade = new Facade(ui, game);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::gameInfoButton()
{

}

void MainWindow::addNeutralButton()
{

}

void MainWindow::addUnitButton()
{

}

void MainWindow::addBaseButton()
{

}

void MainWindow::moveUnitButton()
{

}

void MainWindow::attackButton()
{

}

void MainWindow::baseInfoButton()
{

}

void MainWindow::unitInfoButton()
{

}

void MainWindow::neutralInfoButton()
{

}

void MainWindow::landscapeInfoButton()
{

}
