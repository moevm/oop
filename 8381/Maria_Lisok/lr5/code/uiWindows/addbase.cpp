#include "addbase.h"
#include "ui_addbase.h"

AddBase::AddBase(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddBase)
{
    ui->setupUi(this);
}

AddBase::~AddBase()
{
    delete ui;
}
