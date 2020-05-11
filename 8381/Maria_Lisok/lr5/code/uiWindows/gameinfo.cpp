#include "gameinfo.h"
#include "ui_gameinfo.h"

GameInfo::GameInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameInfo)
{
    ui->setupUi(this);
}

GameInfo::~GameInfo()
{
    delete ui;
}
