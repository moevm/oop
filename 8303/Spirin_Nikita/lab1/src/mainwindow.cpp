#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    example3();

}

void example1()
{
    GameField* gf = new GameField(4, 7);

    Swordsman* swordsman = FactoryOfInfantry().createFirstType();
    Spearman* spearman = FactoryOfInfantry().createSecondType();
    Archer* archer = FactoryOfShooters().createFirstType();
    Crossbowman* crossbowman = FactoryOfShooters().createSecondType();
    HorsemanWithSword* horsemanWithSword = FactoryOfHorsemen().createFirstType();
    HorsemanWithSpear* horsemanWithSpear = FactoryOfHorsemen().createSecondType();

    gf->addUnit(swordsman, 0, 0);
    gf->printField();
    gf->addUnit(spearman, 1, 1);
    gf->printField();
    gf->addUnit(archer, 2, 3);
    gf->printField();
    gf->addUnit(crossbowman, 3, 2);
    gf->printField();
    gf->addUnit(horsemanWithSword, 1, 3);
    gf->printField();
    gf->addUnit(horsemanWithSpear, 3, 1);
    gf->printField();
}

void example2()
{
    GameField* gf = new GameField(4, 7);

    Spearman* spearman = FactoryOfInfantry().createSecondType();
    Archer* archer = FactoryOfShooters().createFirstType();

    gf->addUnit(spearman, 0, 0);
    gf->addUnit(archer, 1, 1);
    gf->printField();

    gf->moveUnit(spearman, 2, 2);
    gf->printField();

    gf->moveUnit(archer, 0, 2);
    gf->printField();
}

void example3()
{
    GameField* gf = new GameField(2, 2);

    HorsemanWithSword* horsemanWithSword = FactoryOfHorsemen().createFirstType();
    HorsemanWithSpear* horsemanWithSpear = FactoryOfHorsemen().createSecondType();

    gf->printField();
    gf->addUnit(horsemanWithSword, 0, 0);
    gf->moveUnit(horsemanWithSword, 1, 1);
    gf->printField();
    gf->moveUnit(horsemanWithSword, 1, 0);
    gf->printField();
    gf->moveUnit(horsemanWithSword, 0, 0);
    gf->printField();
    gf->addUnit(horsemanWithSpear, 0, 1);
    gf->printField();
    gf->moveUnit(horsemanWithSpear, 0, 1);
    gf->printField();
}

MainWindow::~MainWindow()
{
    delete ui;
}

