#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    gameField = new MyGraphicsView();
    ui->gameField->addWidget(gameField);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_create_field_clicked()
{
    int n = ui->size_n->value();
    int m = ui->size_m->value();

    if (field) {
        QMessageBox::warning(this, "Warning", "Поле уже создано!");
        return;
    }

    field = new
            Field(n, m, ui->max_units->value());
    delete gameField;
    gameField = new MyGraphicsView(field);
    ui->gameField->addWidget(gameField);
}



void MainWindow::on_add_unit_clicked()
{
    if (!field) {
        QMessageBox::warning(this, "Warning", "Создайте поле!");
        return;
    }

    if (ui->archer->isChecked()) {
        field->add_unit
                (new Archer(), {ui->x->value(), ui->y->value()});
    } else if (ui->wizard->isChecked()) {
        field->add_unit
                (new Wizard(), {ui->x->value(), ui->y->value()});
    } else if (ui->swordsman->isChecked()) {
        field->add_unit
                (new SwordsMan(), {ui->x->value(), ui->y->value()});
    } else if (ui->spearman->isChecked()) {
        field->add_unit
                (new SpearMan(), {ui->x->value(), ui->y->value()});
    } else if (ui->panzer->isChecked()) {
        field->add_unit
                (new Panzer(), {ui->x->value(), ui->y->value()});
    } else if (ui->centaur->isChecked()) {
        field->add_unit
                (new Centaur(), {ui->x->value(), ui->y->value()});
    }

    gameField->update();
}
