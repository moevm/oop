#include "CreateFieldWindow.h"
#include "ui_createfieldwindow.h"

CreateFieldWindow::CreateFieldWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateFieldWindow)
{
    ui->setupUi(this);
}

CreateFieldWindow::~CreateFieldWindow()
{
    delete ui;
}

void CreateFieldWindow::on_buttonBox_accepted()
{
    if (ui->players_2->isChecked())
        players = Players::PLAYERS_2;
    else
        players = Players::PLAYERS_3;

    if (ui->tenxten->isChecked())
        size = Size::TEN;
    else
        size = Size::FIFTEEN;

    ok = true;
    close();
}

bool CreateFieldWindow::isAccepted()
{
    return ok;
}

void CreateFieldWindow::on_buttonBox_rejected()
{
    ok = false;
    close();
}
