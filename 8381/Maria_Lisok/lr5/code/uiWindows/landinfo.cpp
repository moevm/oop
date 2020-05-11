#include "landinfo.h"
#include "ui_landinfo.h"

LandInfo::LandInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LandInfo)
{
    ui->setupUi(this);
}

LandInfo::~LandInfo()
{
    delete ui;
}
