#include "neutralinfo.h"
#include "ui_neutralinfo.h"

NeutralInfo::NeutralInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NeutralInfo)
{
    ui->setupUi(this);
}

NeutralInfo::~NeutralInfo()
{
    delete ui;
}
