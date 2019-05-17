#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myinterface.h"
#include "loggincategories.h"
#include <exception>
#include "my_except.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_nextNode_clicked()
{
    myInterface::getInstance()->goNext(this->ui);
}

void MainWindow::on_prevNode_clicked()
{
    myInterface::getInstance()->goBack(this->ui);
}

void MainWindow::on_initNode_clicked()
{
    try{
        myInterface::getInstance()->initNode(ui->getFileName->toPlainText(), this->ui);
    }
    catch (MyExcept & ex) {
        ui->status->setText(ex.get_action_error() + " " + ex.data_state);
        return;
    }
}

void MainWindow::on_newNode_clicked()
{
    myInterface::getInstance()->makeNewNode(this->ui);
}

void MainWindow::on_changeNode_clicked()
{
    myInterface::getInstance()->changeMyNode(this->ui);
}

void MainWindow::on_saveButton_clicked()
{
    myInterface::getInstance()->saveInFile();
}

void MainWindow::on_swapButton_clicked()
{
    myInterface::getInstance()->swapNode(this->ui);
}

void MainWindow::on_cacheSaveButton_clicked()
{
    myInterface::getInstance()->saveInCache();
}
