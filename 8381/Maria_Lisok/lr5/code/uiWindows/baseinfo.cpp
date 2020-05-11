#include "baseinfo.h"
#include "ui_baseinfo.h"

BaseInfo::BaseInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BaseInfo)
{
    ui->setupUi(this);
}

BaseInfo::~BaseInfo()
{
    delete ui;
}
