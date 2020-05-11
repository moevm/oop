#include "unitinfo.h"
#include "ui_unitinfo.h"

UnitInfo::UnitInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UnitInfo)
{
    ui->setupUi(this);
}

UnitInfo::~UnitInfo()
{
    delete ui;
}
