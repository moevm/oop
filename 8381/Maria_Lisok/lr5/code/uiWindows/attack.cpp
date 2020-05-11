#include "attack.h"
#include "ui_attack.h"

Attack::Attack(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Attack)
{
    ui->setupUi(this);
}

Attack::~Attack()
{
    delete ui;
}


void Attack::on_buttonBox_accepted()
{

}
