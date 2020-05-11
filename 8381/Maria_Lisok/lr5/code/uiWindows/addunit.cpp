#include "addunit.h"
#include "ui_addunit.h"

AddUnit::AddUnit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUnit)
{
    ui->setupUi(this);

}

AddUnit::~AddUnit()
{
    delete ui;
}



