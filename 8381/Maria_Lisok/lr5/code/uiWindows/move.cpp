#include "move.h"
#include "ui_move.h"

Move::Move(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::move)
{
    ui->setupUi(this);
}

Move::~Move()
{
    delete ui;
}
