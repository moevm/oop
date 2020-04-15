#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, Game *game)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textField->setWordWrapMode(QTextOption::NoWrap);
    ui->pushAddUnit->setDisabled(true);
    ui->pushBaseInfo->setDisabled(true);
    facade = new UIFacade(ui, game);
}

MainWindow::~MainWindow()
{
    delete facade;
    delete ui;
}

void MainWindow::on_actionSet_to_file_triggered()
{
    facade->setLogger(TO_FILE);
}

void MainWindow::on_actionSet_to_terminal_triggered()
{
    facade->setLogger(TO_TERMINAL);
}

void MainWindow::on_actionSet_disabled_triggered()
{
    facade->setLogger(NO_LOGGER);
}

void MainWindow::on_actionSet_short_triggered()
{
    facade->getLogger()->setType(SHORT);
}

void MainWindow::on_actionSet_full_triggered()
{
    facade->getLogger()->setType(FULL);
}


void MainWindow::on_pushAddBase_clicked()
{
    ui->pushAddUnit->setDisabled(false);
    ui->pushBaseInfo->setDisabled(false);
    ui->textOutput->clear();
    facade->addBase(ui->setBaseX->value(), ui->setBaseY->value());
    facade->getItemsInfo();
}

void MainWindow::on_pushGameInfo_clicked()
{
    ui->textOutput->clear();
    facade->getGameInfo();
}

void MainWindow::on_pushBaseInfo_clicked()
{
    ui->textOutput->clear();
    facade->getBaseInfo(ui->comboBases->currentText().toInt());
}

void MainWindow::on_pushAddUnit_clicked()
{
    ui->textOutput->clear();
    facade->addUnit(ui->setUnitX->value(), ui->setUnitY->value(), ui->comboBases->currentText().toInt(), ui->comboBox->currentIndex());
    facade->getBaseInfo(ui->comboBases->currentText().toInt());
    facade->getItemsInfo();
}

void MainWindow::on_pushLandspace_clicked()
{
    facade->getLandspaceInfo();
}

void MainWindow::on_pushMoveUnit_clicked()
{
    ui->textOutput->clear();
    facade->moveItem(ui->setActX->value(), ui->setActY->value(), ui->setDeltaX->value(), ui->setDeltaY->value());
    facade->getItemsInfo();
}

void MainWindow::on_pushItems_clicked()
{
    facade->getItemsInfo();
}

void MainWindow::on_pushAddNeutral_clicked()
{
    ui->textOutput->clear();
    facade->addNeutral(ui->setNeutralX->value(), ui->setNeutralY->value(), ui->comboNeutral->currentIndex()+7);
    facade->getItemsInfo();
}

void MainWindow::on_pushItemInfo_clicked()
{
    ui->textOutput->clear();
    facade->getItemInfo(ui->setItemX->value(), ui->setItemY->value());

}

void MainWindow::on_pushAttack_clicked()
{
    ui->textOutput->clear();
    facade->attackUnit(ui->setActX->value(), ui->setActY->value(), ui->setDeltaX->value(), ui->setDeltaY->value());
    facade->getItemInfo(ui->setItemX->value(), ui->setItemY->value());
    facade->getItemsInfo();
}
